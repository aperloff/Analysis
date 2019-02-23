//custom headers
#include "../KCode/KMap.h"
#include "../KCode/KPlot.h"
#include "../KCode/KLegend.h"
#include "../KCode/KParser.h"

//ROOT headers
#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TLine.h"
//#include "TMath.h"
//#include <TGraphErrors.h>
//#include <TGraphAsymmErrors.h>

//STL headers
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

vector<int> colors = {kBlack,kBlue,kMagenta,kRed,kOrange,kGreen+2,kViolet+2,kGray+2,kTeal-1,kYellow-2};

// Function to find longest common substring. 
string LCSubStr(string X, string Y) 
{ 
    // Find length of both the strings. 
    int m = X.length(); 
    int n = Y.length(); 
  
    // Variable to store length of longest 
    // common substring. 
    int result = 0; 
  
    // Variable to store ending point of 
    // longest common substring in X. 
    int end; 
  
    // Matrix to store result of two 
    // consecutive rows at a time. 
    int len[2][n]; 
  
    // Variable to represent which row of 
    // matrix is current row. 
    int currRow = 0; 
  
    // For a particular value of i and j, 
    // len[currRow][j] stores length of longest 
    // common substring in string X[0..i] and Y[0..j]. 
    for (int i = 0; i <= m; i++) { 
        for (int j = 0; j <= n; j++) { 
            if (i == 0 || j == 0) { 
                len[currRow][j] = 0; 
            } 
            else if (X[i - 1] == Y[j - 1]) { 
                len[currRow][j] = len[1 - currRow][j - 1] + 1; 
                if (len[currRow][j] > result) { 
                    result = len[currRow][j]; 
                    end = i - 1; 
                } 
            } 
            else { 
                len[currRow][j] = 0; 
            } 
        } 
  
        // Make current row as previous row and 
        // previous row as new current row. 
        currRow = 1 - currRow; 
    } 
  
    // If there is no common substring, print -1. 
    if (result == 0) { 
        return "-1"; 
    } 
  
    // Longest common substring is from index 
    // end - result + 1 to index end in X. 
    return X.substr(end - result + 1, result); 
} 

TH1D* histogramMaker(string hname, string htitle, bool longx = false) {
    if(longx)
        return new TH1D(hname.c_str(),htitle.c_str(),96,200,5000); //96 bins = 50 Gev
    else
        return new TH1D(hname.c_str(),htitle.c_str(),16,200,1000); //50 bins = 16 Gev or 16 bins = 50 GeV
    
}

void doGroupAndVar(string group_name, vector<TChain*> chains, string var_group, vector<string> vars, map<string,TCanvas*> &canvases, map<string,vector<TH1D*>> &histograms, string outdir) {

    string cname = group_name+"_"+var_group;
    cout << "Drawing " << cname << " " << flush;

    OptionMap* globalOpt = new OptionMap();
    globalOpt->Set<string>("lumi_text","(13 TeV)");
    globalOpt->Set<double>("sizeSymb",15);
    OptionMap* localOpt = new OptionMap();
    localOpt->Set<bool>("ratio",true);
    localOpt->Set<bool>("logy",false);

    // Check is T1ttt1 is in the list of chains because that will change the range of the histograms
    bool longx = false;
    for(auto c : chains) {
        for(int il=0; il<c->GetNtrees(); il++) {
            if(string(c->GetListOfFiles()->At(il)->GetTitle()).find("T1tttt")!=string::npos) longx = true;
        }
    }

    int fcount(0); //Counter because range based for loops don't have an implicit counter
    for(auto c : chains) {
        cout << "." << flush;
        c->LoadTree(0);
        string fname = c->GetFile()->GetName();

        // Get the TreeMaker production version number
        int pos;
        string version = "PrivProd";
        if(fname.find("Run2ProductionV")!=string::npos) {
            pos = fname.find("Run2ProductionV");
            version = fname.substr(pos+14,3);
        }

        // Remove "_block" from the name if it exists
        if(fname.rfind("_block")!=string::npos) {
            fname.erase(fname.begin()+fname.rfind("_block"),fname.end()-(fname.size()-fname.rfind(".root")));
        }
        if(fname.rfind("_file")!=string::npos) {
            fname.erase(fname.begin()+fname.rfind("_file"),fname.end()-(fname.size()-fname.rfind(".root")));
        }

        // Get only the process name and year of the MC
        pos = fname.rfind("tree_")+5;
        string process_year = fname.substr(pos,fname.size()-pos-5);

        // Get the chained process name and MC year
        string process, mc_year;
        bool isFast = (process_year.find("fast")!=string::npos);
        if(process_year.find("MC")==string::npos) {
            pos = process_year.rfind(".");
            process = (isFast) ? process_year.substr(0,process_year.rfind("_")) : process_year.substr(0,pos);
            mc_year = "SUS-16-033";
        }
        else {
            pos = process_year.rfind("_");
            if (isFast) {
                process_year = process_year.substr(0,pos);
                pos = process_year.rfind("_");
            }
            process = process_year.substr(0,pos);
            mc_year = process_year.substr(pos+1);
        }

        // If the process is HT binned remove the bin values from the process as multiple bins are likely chained
        if(process.find("_HT-")!=string::npos) {
            process = process.substr(0,process.rfind("-"))+"*";
        }
        else if(process.find("SingleLeptFromT")!=string::npos || process.find("DiLept")!=string::npos) {
            process = process.substr(0,process.rfind("_"));
        }

        // Loop through the vars and make the histograms
        for(auto var : vars) {
            bool isGenVar = var.find("Gen")!=string::npos;
            string hname = group_name + "_" + process_year + (isFast ? "_fast_" : "_") + var;
            string htitle = process + (isFast ? "_Fast" : "") + ((vars.size()==2) ? (string(" (") + (isGenVar ? "gen" : "reco") + ")") : "");
            if(histograms.find(cname)==histograms.end()) {
                histograms[cname] = {histogramMaker(hname,htitle,longx)};
            }
            else {
                histograms[cname].push_back(histogramMaker(hname,htitle,longx));
            }
            histograms[cname].back()->Sumw2();
            /*
            string cut = (c->GetNtrees()>1 ? "Weight*(((CrossSection==831.76)*(madHT<600.)*(@GenElectrons.size()==0)*(@GenMuons.size()==0)*(@GenTaus.size()==0)) || " //Inclusive
                                                     "((CrossSection==88.34)*(madHT<600.)*(GenMET<150)) || " //DiLept
                                                     "((CrossSection==5.919026)*(madHT<600.)*(GenMET>=150)) || " //DiLept_genMET150
                                                     "((CrossSection==182.72)*(madHT<600.)*(GenMET<150)) || " //SingleLeptFromT
                                                     "((CrossSection==9.683904)*(madHT<600.)*(GenMET>=150)) || " //SingleLeptFromT_genMET150
                                                     "((CrossSection==182.72)*(madHT<600.)*(GenMET<150)) || " //SingleLeptFromTbar
                                                     "((CrossSection==9.657872)*(madHT<600.)*(GenMET>=150)) || " //SingleLeptFromTbar_genMET150
                                                     "((CrossSection<3.0)*(madHT>=600.)))" : ""); //HT-binned
                                                     */
            string cut = (c->GetNtrees()>1 ? "Weight*(((CrossSection==88.34)*(madHT<600.)) || " //DiLept
                                                     "((CrossSection==182.72)*(madHT<600.)) || " //SingleLeptFromT
                                                     "((CrossSection==182.72)*(madHT<600.)) || " //SingleLeptFromTbar
                                                     "((CrossSection<3.0)*(madHT>=600.)))" : ""); //HT-binned
            if(isGenVar) {
                if(c->GetNtrees()>1) cut +="*";
                cut += "(GenMHT>200.)";
            }
            c->Draw((var+">>"+hname).c_str(),cut.c_str(),"norm pe1 goff");
            histograms[cname].back()->SetMarkerColor(colors[fcount]);
            histograms[cname].back()->SetLineColor(colors[fcount]);
            if(isGenVar) histograms[cname].back()->SetMarkerStyle(kOpenCircle);
            else histograms[cname].back()->SetMarkerStyle(kFullCircle);
            if((histograms[cname].back()->GetMinimum(0.0000001)/histograms[cname].back()->GetMaximum())<0.01) {
                localOpt->Set<bool>("logy",true);
            }
            histograms[cname].back()->SetDirectory(0);
        }

        fcount++;
    }

    // Make the canvas frame
    bool hasRatio = false; localOpt->Get<bool>("ratio",hasRatio);
    bool isLogy = false; localOpt->Get<bool>("logy",isLogy);
    auto h_ymin = std::min_element(histograms[cname].begin(), histograms[cname].end(), []( TH1D const * h1, TH1D const * h2){return h1->GetMinimum(1e-12) < h2->GetMinimum(1e-12);});
    auto h_ymax = std::max_element(histograms[cname].begin(), histograms[cname].end(), []( TH1D const * h1, TH1D const * h2){return h1->GetMaximum() < h2->GetMaximum();});
    auto hMinAndMax = make_pair((*h_ymin)->GetMinimum(1e-12)*0.9,(*h_ymax)->GetMaximum()*(isLogy ? 10.0 : 1.10));
    TH1D* frame = histogramMaker("Frame_"+cname,"Frame_"+cname,longx);
    frame->GetYaxis()->SetRangeUser(hMinAndMax.first,hMinAndMax.second);
    string var_group_title;
    if(var_group=="MET")                                   var_group_title = "E_{T}^{miss} [GeV]";
    else if (var_group=="MHT" || var_group=="GenMHTVsMHT") var_group_title = "H_{T}^{miss} [GeV]";
    else if (var_group=="GenMHT")                          var_group_title = "H_{T}^{miss,gen} [GeV]";
    else if (var_group=="HT")                              var_group_title = "H_{T} [GeV]";
    else if (var_group=="madHT")                           var_group_title = "H_{T}^{madgraph} [GeV]";
    else                                                   var_group_title = var_group;
    frame->GetXaxis()->SetTitle(var_group_title.c_str());
    frame->GetYaxis()->SetTitle("a.u.");

    KPlot* plot = new KPlot(cname,localOpt,globalOpt);
    plot->Initialize(frame);
    KLegend* kleg = plot->GetLegend();
    canvases[cname] = plot->GetCanvas();
    TPad* pad1 = plot->GetPad1();
    TPad* pad2 = plot->GetPad2();

    // Build the legend
    // Legend placement options: (right,left)
    KLegend::Horz legside = KLegend::right;
    vector<string> fields;
    KParser::process(group_name,'_',fields);
    string legheader = (fields.size()==2) ? fields[0]+": "+fields[1] : group_name;
    //kleg->GetLegend()->SetHeader((legheader).c_str());
    kleg->AddEntry((TObject*)0,legheader.c_str(),"");
    for(auto h : histograms[cname]) {
        if(string(h->GetName()).find("ratio")!=string::npos || string(h->GetName()).find("corrected")!=string::npos) continue;
        kleg->AddEntry(h,h->GetTitle(),"LP");
    }
    kleg->Build(legside,KLegend::top);

    // Draw histograms
    pad1->cd();
    plot->DrawHist();
    for(auto h : histograms[cname]) {
        if(string(h->GetName()).find("ratio")!=string::npos || string(h->GetName()).find("corrected")!=string::npos) continue;
        h->Draw("norm pe1 same");
    }
    plot->GetHisto()->Draw("sameaxis"); //draw again so axes on top
    plot->DrawText();

    if(hasRatio) {
        // Draw the ratio histograms
        pad2->cd();
        //plot->GetRatio()->GetYaxis()->SetRangeUser(hMinAndMax.first,hMinAndMax.second);
        //pad2->SetLogy();
        //plot->GetRatio()->GetYaxis()->SetTitle("(gen+reco)/2");
        string ytitle = (vars.size()==2) ? "Gen/Reco" : (group_name.find("vs")!=string::npos) ? "V12/V16" : "Full/Fast";
        plot->GetRatio()->GetYaxis()->SetTitle(ytitle.c_str());
        plot->DrawRatio();
        TLine* centerLine = new TLine(plot->GetRatio()->GetXaxis()->GetXmin(),1.0,plot->GetRatio()->GetXaxis()->GetXmax(),1.0);
        centerLine->SetLineStyle(kDashed);
        centerLine->Draw("same");
        int offset = (vars.size()==2 || group_name.find("vs")!=string::npos) ? 0 : 1;
        for(unsigned ih=(0+offset); ih<histograms[cname].size(); ih+=3) {
            // Create the ratio histogram and draw it
            string hname = histograms[cname][ih]->GetName();
            string denomname = histograms[cname][ih+1]->GetName();
            hname += "_"+denomname.substr(denomname.rfind("_")+1,denomname.size()-denomname.rfind("_")+1)+"_ratio";
            histograms[cname].insert(histograms[cname].begin()+ih+2,(TH1D*)histograms[cname][ih]->Clone(hname.c_str()));
            histograms[cname][ih+2]->Divide(histograms[cname][ih+1]);
            histograms[cname][ih+2]->Draw("pe1 same");
        }
        plot->GetRatio()->Draw("sameaxis"); //draw again so axes on top
    }

    cout << " DONE" << endl;
    // Save the current canvas
    canvases[cname]->Modified();
    canvases[cname]->Update();
    canvases[cname]->Print((outdir+cname+".eps").c_str());
}

/*
Example: root -n fastFullMHTCorrection.C+\(\"plots_FastFullMHTCorrection\"\)
*/
int fastFullMHTCorrection(string outdir="./") {
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    if(outdir.back()!='/') outdir += "/";

    string redirector="root://cmseos.fnal.gov/";
    map<string,vector<vector<string>>> filenames = {
                                                        /*
                                                        {"V16_MC2016",
                                                            {
                                                                //{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_TTJets_MC2016.root"},
                                                                {
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_TTJets_SingleLeptFromT_MC2016.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_TTJets_SingleLeptFromTbar_MC2016.root",
                                                                    //"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_TTJets_DiLept_MC2016.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_TTJets_HT-600to800_MC2016.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_TTJets_HT-800to1200_MC2016.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_TTJets_HT-1200to2500_MC2016.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_TTJets_HT-2500toInf_MC2016.root",
                                                                },
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_T2tt_225_50_MC2016.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_signal/tree_T2tt_225_50_MC2016_fast.root"},
                                                                //{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_T2tt_425_325_MC2016.root"},
                                                                //{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_signal/tree_T2tt_425_325_MC2016_fast.root"},
                                                            }
                                                        },
                                                        {"V12_SUS-16-033",
                                                            {
                                                                //{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets.root"},
                                                                {
                                                                    //"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_SingleLeptFromT.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_SingleLeptFromTbar.root",
                                                                    //"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_DiLept.root",
                                                                    //"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_SingleLeptFromT_genMET-150.root",
                                                                    //"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_SingleLeptFromTbar_genMET-150.root",
                                                                    //"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_DiLept_genMET-150.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_HT-600to800.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_HT-800to1200.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_HT-1200to2500.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_HT-2500toInf.root",
                                                                },
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_T2tt_225_50.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_signal/tree_T2tt_225_50_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_T2tt_425_325.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_signal/tree_T2tt_425_325_fast.root"},
                                                            }
                                                        },
                                                        {"alphaT_SUS-16-033",
                                                            {
                                                                //{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_T2tt_300_125.root"},
                                                                //{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_T2tt_175_1_fast.root"}, 
                                                                {
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_HT-600to800.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_HT-800to1200.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_HT-1200to2500.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_TTJets_HT-2500toInf.root",
                                                                },  
                                                            }
                                                        },
                                                        */
                                                        {"V12vsV16",
                                                            {
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_signal/tree_T2tt_225_50_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_signal/tree_T2tt_225_50_MC2016_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_signal/tree_T1tttt_2000_100_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_signal/tree_T1tttt_2000_100_MC2016_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_signal/tree_T1tttt_2000_1600_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_signal/tree_T1tttt_2000_1600_MC2016_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_signal/tree_T1tttt_1000_100_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_signal/tree_T1tttt_1000_100_MC2016_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_signal/tree_T1tttt_1000_775_fast.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_signal/tree_T1tttt_1000_775_MC2016_fast.root"},
                                                            }
                                                        }
                                                   };

    map<string,vector<string>> vars = {
                                        {"GenMHTVsMHT",
                                            {"GenMHT","MHT"}
                                        },
                                        {"GenMHT",
                                            {"GenMHT"}
                                        },
                                        {"MHT",
                                            {"MHT"}
                                        },
                                        {"MET",
                                            {"MET"}
                                        },
                                        {"HT",
                                            {"HT"}
                                        },
                                        {"madHT",
                                            {"madHT"}
                                        }
                                      };

    map<string,TCanvas*> canvases;
    map<string,vector<TH1D*>> histograms;

    for(auto it_group=filenames.begin(); it_group!=filenames.end(); it_group++) {
        vector<TChain*> chains;

        // Open files for a given group
        for(auto it_chain=it_group->second.begin(); it_chain!=it_group->second.end(); it_chain++) {
            chains.push_back(new TChain("tree"));
            for(auto it_file=it_chain->begin(); it_file!=it_chain->end(); it_file++) {
                cout << "Adding file " << redirector << *it_file << " ... " << flush;
                chains.back()->AddFile((redirector+*it_file).c_str());
                cout << "DONE" << endl;
            }
        }

        // Loop over vars to print
        for(auto it_var=vars.begin(); it_var!=vars.end(); it_var++) {
            doGroupAndVar(it_group->first,chains,it_var->first,it_var->second,canvases,histograms,outdir);
        }
    }

    return 0;
}