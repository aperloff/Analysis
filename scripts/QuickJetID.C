#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TLine.h"
#include "TMath.h"
#include "TMathText.h"
#include "TLatex.h"

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using std::cout;
using std::endl;
using std::flush;
using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::min_element;
using std::max_element;

vector<int> colors = {kRed,kBlue,kBlack,kRed+2,kBlue+2,kGray+1,kMagenta+1,kViolet+1};

TH1D* histogramMaker(string var,string hname, string htitle) {
    return (var.find("Multiplicity")!=string::npos) ? new TH1D(hname.c_str(),htitle.c_str(),25,0,25) : new TH1D(hname.c_str(),htitle.c_str(),35,0,1.4);
}

void doGroupAndVar(string group_name, vector<TChain*> chains, string var, vector<pair<string,string>> regions,
                   map<pair<string,string>,pair<float,float>> cuts,map<string,TCanvas*> &canvases, map<string,vector<TH1D*>> &histograms,
                   string outdir) {

    auto legend = new TLegend(0.519306,0.6982261,0.8987697,0.8983086);
    auto latex = new TLatex();
    latex->SetTextFont(42);
    latex->SetTextSize(0.035);
    latex->SetTextAlign(31);
    latex->SetNDC();
    //auto pave = new TPaveText(0.519306,0.59,0.8987697,0.6982261);
    //pave->SetFillColor(kNone);
    //pave->SetLineColor(kNone);
    //pave->SetFillStyle(0);
    //pave->SetLineWidth(0);
    bool ldone = false;

    for(auto region : regions) {
        string cname = group_name+"_"+var.substr(5,var.size()-5)+"_"+region.first;
        cout << "Drawing " << cname << " " << flush;
        canvases[cname] = new TCanvas(cname.c_str(),cname.c_str(),800,800);
        canvases[cname]->cd();
        //pave->Clear();
        bool isLog = false;
        int fcount = 0;
        string option;
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
            string hname = group_name+"_"+process_year+"_"+var.substr(5,var.size()-5)+"_"+region.first;

            // Get the histogram title
            pos = process_year.rfind("_");
            string process, mc_year;
            bool isFast = false;
            if(process_year.find("fast")==string::npos) {
                process = process_year.substr(0,pos);
                mc_year = process_year.substr(pos+1);
                if(process.find("SingleMuon")!=string::npos || process.find("JetHT")!=string::npos) {
                    // Remove the run period letter
                    mc_year = mc_year.substr(0,mc_year.size()-1);
                }
            }
            else {
                isFast = true;
                process_year = process_year.substr(0,pos);
                pos = process_year.rfind("_");
                process = process_year.substr(0,pos);
                mc_year = process_year.substr(pos+1);
            }
            if(mc_year.find("MC")==string::npos && process.find("SingleMuon")==string::npos && process.find("JetHT")==string::npos) {
                mc_year = "SUS-16-033";
            }
            string htitle = process+" ("+version;
            if(isFast) htitle += "Fast";
            htitle += ": "+mc_year+")";

            if(histograms.find(cname)==histograms.end()) {
                histograms[cname] = {histogramMaker(var,hname,htitle)};
            }
            else {
                histograms[cname].push_back(histogramMaker(var,hname,htitle));
            }
            histograms[cname].back()->Sumw2();
            option = (fcount==0) ? "norm pe1 goff" : "norm pe1 same goff";
            c->Draw(("("+var+(var.find("Fraction")!=string::npos && mc_year.find("MC")!=string::npos? "*Jets_jerFactor)" : ")")+">>"+hname).c_str(),
                    (region.second + " && Jets.Pt()>30" + (fname.find("JetHT")!=string::npos ? " && Jets[0].Pt()>60" : "")).c_str(),
                    option.c_str());
            histograms[cname].back()->SetMarkerColor(colors[fcount]);
            histograms[cname].back()->SetLineColor(colors[fcount]);
            if(isFast) histograms[cname].back()->SetMarkerStyle(kOpenCircle);
            else histograms[cname].back()->SetMarkerStyle(kFullCircle);
            if((histograms[cname].back()->GetMinimum(0.0000001)/histograms[cname].back()->GetMaximum())<0.01) {
                canvases[cname]->SetLogy();
                isLog = true;
            }

            if(!ldone) legend->AddEntry(histograms[cname].back(),htitle.c_str(),"LP");
            fcount++;
        }

        canvases[cname]->cd();

        // Make the canvas frame
        auto h_ymin = std::min_element(histograms[cname].begin(), histograms[cname].end(), []( TH1D const * h1, TH1D const * h2){return h1->GetMinimum(1e-12) < h2->GetMinimum(1e-12);});
        auto h_ymax = std::max_element(histograms[cname].begin(), histograms[cname].end(), []( TH1D const * h1, TH1D const * h2){return h1->GetMaximum() < h2->GetMaximum();});
        auto hMinAndMax = make_pair((*h_ymin)->GetMinimum(1e-12)*0.9,(*h_ymax)->GetMaximum()*((var.find("Multiplicity")&&isLog) ? 10.0 : 1.10));
        if(region.first.find("barrel")!=string::npos && (var.find("neutralEmEnergyFraction")!=string::npos||var.find("neutralHadronEnergyFraction")!=string::npos)) {
            hMinAndMax = make_pair(1.0e-7,1.0);
        }
        TH1D* frame = histogramMaker(var,"Frame_"+cname,"Frame_"+cname);
        frame->GetYaxis()->SetRangeUser(hMinAndMax.first,hMinAndMax.second);
        frame->GetXaxis()->SetTitle(var.c_str());
        frame->Draw();
        for(auto h : histograms[cname]) {
            h->Draw(option.c_str());
        }
        canvases[cname]->Modified();
        canvases[cname]->Update();

        // Plot the lines for the cuts
        auto it_cut = cuts.find(make_pair(var,region.first));
        if(it_cut!=cuts.end()) {
            TLine* line;
            auto cMinAndMax = make_pair( (isLog) ? TMath::Power(10.0,canvases[cname]->GetUymin()) : canvases[cname]->GetUymin(),
                                         (isLog) ? TMath::Power(10.0,canvases[cname]->GetUymax()) : canvases[cname]->GetUymax());
            auto cut = it_cut->second;
            // cout << "Min: " << cMinAndMax.first << " Max: " << cMinAndMax.second << endl;
            // cout << "c1: " << cut.first << " c2: " << cut.second << endl;
            if(cut.first!=-1.0) {
                line = new TLine(cut.first,cMinAndMax.first,cut.first,cMinAndMax.second);
                line->SetLineStyle(kDotted);
                line->SetLineColor(kGreen);
                line->SetLineWidth(2);
                line->Draw("same");
            }
            if(cut.second!=-1.0) {
                line = new TLine(cut.second,cMinAndMax.first,cut.second,cMinAndMax.second);
                line->SetLineStyle(kDotted);
                line->SetLineColor(kOrange);
                line->SetLineWidth(2);
                line->Draw("same");
            }
        }
        else {
            cout << "WARNING::doGroupAndVar::Can't find cuts!" << endl;
        }

        // Draw the legend
        legend->Draw("same");
        if(!ldone) ldone = true;

        //Draw the region
        string region_text;
        if(region.first.find("barrel")!=string::npos) region_text = "\\text{Region 1:}~|\\eta|\\leq2.7";
        else if(region.first.find("endcap")!=string::npos) region_text = "\\text{Region 2:}~2.7<|\\eta|\\leq3.0";
        else if(region.first.find("forward")!=string::npos) region_text = "\\text{Region 3:}~3.0<|\\eta|\\leq5.0";
        else if(region.first.find("tracker")!=string::npos) region_text = "\\text{Region 1':}~|\\eta|\\leq2.4";
        else if(region.second.find("<=")!=string::npos || region.second.find(">")!=string::npos) {
            if(region.second.find(">")!=string::npos) {
                region_text += region.second.substr(region.second.find(">")+1,3) + "<";
            }
            region_text += "|\\eta|";
            if(region.second.find("<=")!=string::npos) {
                region_text += "\\leq" + region.second.substr(region.second.find("<=")+2,3);
            }
        }
        else {
            cout << "WARNING::doGroupAndVar::Can't find eta region!" << endl;
        }
        //pave->AddText(region_text.c_str());
        //pave->DrawClone("same");
        latex->DrawLatexNDC(0.9,0.92,region_text.c_str());
        //latex->DrawMathText(0.9,0.92,region_text.c_str());

        cout << " DONE" << endl;
        // Save the current canvas
        canvases[cname]->Modified();
        canvases[cname]->Update();
        canvases[cname]->Print((outdir+cname+".eps").c_str());
    }
}

/*
Example: root -n QuickJetID.C+\(\"plots/\"\)
*/
int QuickJetID(string outdir="./") {
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    if(outdir.back()!='/') outdir += "/";

    string redirector="root://cmseos.fnal.gov/";
    map<string,vector<vector<string>>> filenames = {
                                                        //{"FullSimVsFastSim_signal_T1tttt_2000_100",
                                                        //    {{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/tree_signal/tree_T1tttt_2000_100.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_T1tttt_2000_100_MC2016.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/tree_T1tttt_2000_100_MC2017.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan/tree_signal/tree_T1tttt_2000_100_fast.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_signal/tree_T1tttt_2000_100_MC2016_fast.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/scan/tree_signal/tree_T1tttt_2000_100_MC2017_fast.root"}}
                                                        //},
                                                        //{"DYm_CleanVars_2016",
                                                        //    {{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_DYJetsToLL_M-50_MC2016.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_TTJets_MC2016.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2016B.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2016C.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2016D.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2016E.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2016F.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2016G.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2016H.root"}}
                                                        //},
                                                        //{"DYm_CleanVars_2017",
                                                        //    {{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_DYJetsToLL_M-50_MC2017.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_TTJets_MC2017.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2017B.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2017C.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2017D.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2017E.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_DYm_CleanVars/tree_SingleMuon_2017F.root"}}
                                                        //}
                                                        //{"SLm_2016",
                                                        //    {{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_WJetsToLNu_HT-100to200_MC2016.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_WJetsToLNu_HT-200to400_MC2016.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_WJetsToLNu_HT-800to1200_MC2016.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_WJetsToLNu_HT-1200to2500_MC2016.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_TTJets_MC2016.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016C.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016D.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016E.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016F.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016G.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016H.root"}}
                                                        //},
                                                        //{"SLm_2017",
                                                        //    {{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_WJetsToLNu_HT-100to200_MC2017.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_WJetsToLNu_HT-200to400_MC2017.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_WJetsToLNu_HT-800to1200_MC2017.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_WJetsToLNu_HT-1200to2500_MC2017.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_TTJets_MC2017.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017C.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017D.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017E.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017F.root"}}
                                                        //},
                                                        //{"SLm_Data",
                                                        //    {{"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016C.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016D.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016E.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016F.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016G.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016H.root"},
                                                        //     {"/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017C.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017D.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017E.root",
                                                        //      "/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017F.root"}}
                                                        //}
                                                        //{"FullSim_SignalRegion_NoBuiltInJetIDCut",
                                                        //    {{"/store/user/rgp230/SUSY/JetID/tree_T1tttt_2000_100_MC2016.root"},
                                                        //     {"/store/user/rgp230/SUSY/JetID/tree_T1tttt_2000_100_MC2017.root"}}
                                                        //},
                                                        //{"FullSim_SLm_NoBuiltInJetIDCut",
                                                        //    {
                                                        //        {"/store/user/rgp230/SUSY/JetID/tree_SLm/tree_SingleMuon_2016B.root"},
                                                        //        {"/store/user/rgp230/SUSY/JetID/tree_SLm/tree_SingleMuon_2017B.root"},
                                                        //        {"/store/user/rgp230/SUSY/JetID/tree_SLm/tree_TTJets_SingleLeptFromT_MC2016.root"},
                                                        //        {"/store/user/rgp230/SUSY/JetID/tree_SLm/tree_TTJets_SingleLeptFromT_MC2017.root"}
                                                        //    }
                                                        //},
                                                        //{"FullSim_T1ttttSignal_TTJetsSingleLepFromTSLm_NoBuiltInJetIDCut",
                                                        //    {
                                                        //        {"/store/user/rgp230/SUSY/JetID/tree_T1tttt_2000_100_MC2016.root"},
                                                        //        {"/store/user/rgp230/SUSY/JetID/tree_T1tttt_2000_100_MC2017.root"},
                                                        //        {"/store/user/rgp230/SUSY/JetID/tree_SLm/tree_TTJets_SingleLeptFromT_MC2016.root"},
                                                        //        {"/store/user/rgp230/SUSY/JetID/tree_SLm/tree_TTJets_SingleLeptFromT_MC2017.root"},
                                                        //        {Data}
                                                        //    }
                                                        //},
                                                        {"FullSim_MCandData_NoBuiltInJetIDCut",
                                                            {
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_signal/tree_T1tttt_2000_100_MC2016.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_signal/tree_T1tttt_2000_100_MC2017.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_TTJets_SingleLeptFromT_MC2016.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_TTJets_SingleLeptFromT_MC2017.root"},
                                                                {
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block0.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block1.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block2.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block3.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block4.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block5.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block6.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block7.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block8.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block9.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block10.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block11.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block12.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block13.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block14.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block15.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block16.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block17.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2016B_block18.root"
                                                                },
                                                                {
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block0.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block1.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block2.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block3.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block4.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block5.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block6.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block7.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block8.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block9.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block10.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block11.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block12.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block13.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block14.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block15.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block16.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block17.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block18.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block19.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block20.root",
                                                                    "/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_SLm/tree_SingleMuon_2017B_block21.root"
                                                                },
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_signal/tree_JetHT_2017B_files0to9.root"},
                                                                {"/store/user/lpcsusyhad/SusyRA2Analysis2015/PFJetIDStudies/Run2ProductionV16/tree_signal/tree_QCD_HT-500to700_MC2017_files0to9.root"}
                                                            }
                                                        },
                                                   };

    vector<string> vars = {"Jets_neutralEmEnergyFraction","Jets_neutralHadronEnergyFraction","Jets_chargedEmEnergyFraction","Jets_chargedHadronEnergyFraction","Jets_neutralMultiplicity","Jets_chargedMultiplicity"};
    //vector<string> vars = {"Jets_chargedEmEnergyFraction"};
    //vector<string> vars = {"Jets_neutralEmEnergyFraction","Jets_neutralHadronEnergyFraction"};

    //vector<pair<string,string>> regions = {make_pair("barrel","abs(Jets.Eta())<=2.7"),make_pair("endcap","abs(Jets.Eta())>2.7 && abs(Jets.Eta())<=3.0"),make_pair("forward","abs(Jets.Eta())>3.0")};
    vector<pair<string,string>> regions = {make_pair("0p0to0p5","abs(Jets.Eta())<=0.5"),make_pair("0p5to1p0","abs(Jets.Eta())>0.5 && abs(Jets.Eta())<=1.0"),
                                           make_pair("1p0to1p5","abs(Jets.Eta())>1.0 && abs(Jets.Eta())<=1.5"),make_pair("1p5to2p0","abs(Jets.Eta())>1.5 && abs(Jets.Eta())<=2.0"),
                                           make_pair("2p0to2p7","abs(Jets.Eta())>2.0 && abs(Jets.Eta())<=2.7"),make_pair("2p7to3p0","abs(Jets.Eta())>2.7 && abs(Jets.Eta())<=3.0"),
                                           make_pair("3p0to5p0","abs(Jets.Eta())>3.0 && abs(Jets.Eta())<=5.0")};
    //vector<pair<string,string>> regions = {make_pair("barrel","abs(Jets.Eta())<2.7"),make_pair("endcap","abs(Jets.Eta())>2.7 && abs(Jets.Eta())<3.0")};
    //vector<pair<string,string>> regions = {make_pair("endcap","abs(Jets.Eta())>2.7 && abs(Jets.Eta())<3.0")};
    //vector<pair<string,string>> regions = {make_pair("barrel","abs(Jets.Eta())<2.7")};
    //vector<pair<string,string>> regions = {make_pair("tracker","abs(Jets.Eta())<2.4")};
    //vector<pair<string,string>> regions = {make_pair("barrel_JetID","abs(Jets.Eta())<2.7 && JetID"),make_pair("barrel_notJetID","abs(Jets.Eta())<2.7 && !JetID"),make_pair("tracker_JetID","abs(Jets.Eta())<2.4 && JetID")};

    map<pair<string,string>,pair<float,float>> cuts = {make_pair(make_pair("Jets_neutralEmEnergyFraction","barrel"), make_pair(-1.0,0.90)),
                                                       make_pair(make_pair("Jets_neutralEmEnergyFraction","endcap"), make_pair(0.02,0.99)),
                                                       make_pair(make_pair("Jets_neutralEmEnergyFraction","forward"),make_pair(-1.0,0.90)),
                                                       make_pair(make_pair("Jets_neutralEmEnergyFraction","tracker"),make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_neutralEmEnergyFraction","barrel_JetID"), make_pair(-1.0,0.90)),
                                                       make_pair(make_pair("Jets_neutralEmEnergyFraction","barrel_notJetID"), make_pair(-1.0,0.90)),
                                                       make_pair(make_pair("Jets_neutralEmEnergyFraction","tracker_JetID"),make_pair(-1.0,0.90)),
                                                       make_pair(make_pair("Jets_neutralHadronEnergyFraction","barrel"), make_pair(-1.0,0.90)),
                                                       make_pair(make_pair("Jets_neutralHadronEnergyFraction","endcap"), make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_neutralHadronEnergyFraction","forward"),make_pair(0.02,-1.0)),
                                                       make_pair(make_pair("Jets_neutralHadronEnergyFraction","tracker"),make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_neutralHadronEnergyFraction","barrel_JetID"), make_pair(-1.0,0.90)),
                                                       make_pair(make_pair("Jets_neutralHadronEnergyFraction","barrel_notJetID"), make_pair(-1.0,0.90)),
                                                       make_pair(make_pair("Jets_neutralHadronEnergyFraction","tracker_JetID"),make_pair(-1.0,0.90)),
                                                       make_pair(make_pair("Jets_chargedHadronEnergyFraction","barrel"), make_pair(0.00,-1.0)),
                                                       make_pair(make_pair("Jets_chargedHadronEnergyFraction","endcap"), make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_chargedHadronEnergyFraction","forward"),make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_chargedHadronEnergyFraction","tracker"),make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_chargedHadronEnergyFraction","barrel_JetID"), make_pair(0.00,-1.0)),
                                                       make_pair(make_pair("Jets_chargedHadronEnergyFraction","barrel_notJetID"), make_pair(0.00,-1.0)),
                                                       make_pair(make_pair("Jets_chargedHadronEnergyFraction","tracker_JetID"),make_pair(0.00,-1.0)),
                                                       make_pair(make_pair("Jets_neutralMultiplicity","barrel"), make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_neutralMultiplicity","endcap"), make_pair(2.00,-1.0)),
                                                       make_pair(make_pair("Jets_neutralMultiplicity","forward"),make_pair(10.0,-1.0)),
                                                       make_pair(make_pair("Jets_neutralMultiplicity","tracker"),make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_neutralMultiplicity","barrel_JetID"), make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_neutralMultiplicity","barrel_notJetID"), make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_neutralMultiplicity","tracker_JetID"),make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_chargedMultiplicity","barrel"), make_pair(0.00,-1.0)),
                                                       make_pair(make_pair("Jets_chargedMultiplicity","endcap"), make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_chargedMultiplicity","forward"),make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_chargedMultiplicity","tracker"),make_pair(-1.0,-1.0)),
                                                       make_pair(make_pair("Jets_chargedMultiplicity","barrel_JetID"), make_pair(0.00,-1.0)),
                                                       make_pair(make_pair("Jets_chargedMultiplicity","barrel_notJetID"), make_pair(0.00,-1.0)),
                                                       make_pair(make_pair("Jets_chargedMultiplicity","tracker_JetID"),make_pair(0.00,-1.0)),
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
            // Eta regions handled inside this function
            doGroupAndVar(it_group->first,chains,*it_var,regions,cuts,canvases,histograms,outdir);
        }
    }

    return 0;
}