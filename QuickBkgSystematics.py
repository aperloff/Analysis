from ROOT import *
import math, os, argparse

def do_hadd(indir, CR):
    CRe = CR[:2]+"e"+CR[2:]
    CRm = CR[:2]+"m"+CR[2:]
    os.system("hadd "+indir+"RA2bin_"+CR+"_TotalBkg.root "+indir+"RA2bin_"+CRe+"_TotalBkg.root "+indir+"RA2bin_"+CRm+"_TotalBkg.root")

def hadd_if_necessary(indir, CR):
    #Run the hadding processes for SL and DY first, if necessary
    CRe  = CR[:2]+"e"+CR[2:]
    CRm  = CR[:2]+"m"+CR[2:]
    CRem = CR[:2]+"\{e,m\}"+CR[2:]
    if os.path.isfile(indir+"RA2bin_"+CRe+"_TotalBkg.root") and os.path.isfile(indir+"RA2bin_"+CRm+"_TotalBkg.root"):
        if not os.path.isfile(indir+"RA2bin_"+CR+"_TotalBkg.root"):
            print indir+"RA2bin_"+CR+"_TotalBkg.root is missing. Will hadd to make a new one."
            do_hadd(indir, CR)
        elif os.path.getmtime(indir+"RA2bin_"+CR+"_TotalBkg.root") < os.path.isfile(indir+"RA2bin_"+CRe+"_TotalBkg.root") or \
             os.path.getmtime(indir+"RA2bin_"+CR+"_TotalBkg.root") < os.path.isfile(indir+"RA2bin_"+CRm+"_TotalBkg.root"):
            print indir+"RA2bin_"+CR+"_TotalBkg.root is out-of-date. Will re-create."
            os.system("rm "+indir+"RA2bin_"+CR+"_TotalBkg.root")
            do_hadd(indir, CR)
        else:
            print indir+"RA2bin_"+CR+"_TotalBkg.root is up-to-date. No action required."
    else:
        print "Missing one or more of the "+CRem+" files"
        exit(-1)

def make_bkg_systematics(indir, outdir, suffix, lumi):
    fin=TFile(indir+"RA2bin_signal_TotalBkg.root", "READ")
    #4 main RA2 bkgs
    TTJetsBkgSR=fin.Get("RA2bin_TTJets_nominal")
    WJetBkgSR=fin.Get("RA2bin_WJet_nominal")
    ZInvBkgSR=fin.Get("RA2bin_ZInv_nominal")
    QCDBkgSR=fin.Get("RA2bin_QCD_nominal")
    ZInvBkgSR.Scale(lumi)
    WJetBkgSR.Scale(lumi)
    TTJetsBkgSR.Scale(lumi)
    QCDBkgSR.Scale(lumi)

    # Control Regions
    finSL=TFile(indir+"RA2bin_SL_TotalBkg.root", "READ");
    TTJetsSL=finSL.Get("RA2bin_TTJets_nominal");
    WJetsSL=finSL.Get("RA2bin_WJet_nominal");
    TTJetsSL.Add(WJetsSL); #Total Single Lepton
    TTJetsSL.Scale(lumi)
    output=TFile(outdir+"BkgInputCards"+suffix+".root","RECREATE");
    TFSingleLepton=TTJetsBkgSR.Clone("TFSingleLepton")
    TFSingleLepton.Reset();
    TFLowDphi=QCDBkgSR.Clone("TFLowDphi")
    TFLowDphi.Reset();
    TFDY=ZInvBkgSR.Clone("TFDY")
    TFDY.Reset();

    for i in range(0,TTJetsSL.GetNbinsX()):
        TF=1.0;
        if(TTJetsSL.GetBinContent(i+1)>0):TF=(TTJetsBkgSR.GetBinContent(i+1)+WJetBkgSR.GetBinContent(i+1))/TTJetsSL.GetBinContent(i+1)
        TFSingleLepton.SetBinContent(i+1,TF);
        if TTJetsSL.GetBinContent(i+1)>1: 
            TTJetsSL.SetBinError(i+1, math.sqrt(TTJetsSL.GetBinContent(i+1)));
        else:
            TTJetsSL.SetBinError(i+1, TF);
            TTJetsSL.SetBinContent(i+1, 0.0) #use gamma function for less than 2 events

    finLDP=TFile(indir+"RA2bin_LDP_TotalBkg.root", "READ");
    LDPYields=finLDP.Get("RA2bin_QCD_nominal") #Low DPhi Yields 
    for i in range(0,LDPYields.GetNbinsX()):
        TF=1.0;
        if(LDPYields.GetBinContent(i+1)>0):TF=QCDBkgSR.GetBinContent(i+1)/LDPYields.GetBinContent(i+1);     
        TFLowDphi.SetBinContent(i+1, TF);
        if LDPYields.GetBinContent(i+1)>1: 
            LDPYields.SetBinError(i+1, math.sqrt(LDPYields.GetBinContent(i+1)));
        else:
            LDPYields.SetBinError(i+1,TF);
            LDPYields.SetBinContent(i+1,0)  

    LDPYields.Scale(lumi);

    finGJets=TFile(indir+"RA2bin_GJet_CleanVars_TotalBkg.root","READ");
    GJetsYields=finGJets.Get("RA2bin_GJets_nominal");
    finDY=TFile(indir+"RA2bin_DY_CleanVars_TotalBkg.root","READ");
    DYYields=finDY.Get("RA2bin_DY_nominal");
    DYYields.Scale(lumi);
    for i in range(0,DYYields.GetNbinsX()):
        TF=1.0;
        if(DYYields.GetBinContent(i+1)>0):TF=ZInvBkgSR.GetBinContent(i+1)/DYYields.GetBinContent(i+1);      
        TFDY.SetBinContent(i+1, TF);
        if DYYields.GetBinContent(i+1)>1: 
            DYYields.SetBinError(i+1, math.sqrt(DYYields.GetBinContent(i+1)));
        else:
            DYYields.SetBinError(i+1,TF);
            DYYields.SetBinContent(i+1,0)   
    ZInvBkgSR.SetFillStyle(1001);
    ZInvBkgSR.SetFillColor(kRed);
    TTJetsBkgSR.SetFillStyle(1001);
    TTJetsBkgSR.SetFillColor(kBlue)
    TTJetsBkgSR.Add(WJetBkgSR)
    QCDBkgSR.SetFillColor(kYellow)
    QCDBkgSR.SetFillStyle(1001);

    #############SET THE BIN ERROR Based on the CS Yields
    for i in range(0, ZInvBkgSR.GetNbinsX()):
        if DYYields.GetBinContent(i+1)>0:ZInvBkgSR.SetBinError(i+1,  ZInvBkgSR.GetBinContent(i+1)*DYYields.GetBinError(i+1)/DYYields.GetBinContent(i+1))
        if LDPYields.GetBinContent(i+1)>0:QCDBkgSR.SetBinError(i+1, QCDBkgSR.GetBinContent(i+1)*LDPYields.GetBinError(i+1)/LDPYields.GetBinContent(i+1))
        if TTJetsSL.GetBinContent(i+1)>0:TTJetsBkgSR.SetBinError(i+1, TTJetsBkgSR.GetBinContent(i+1)*TTJetsSL.GetBinError(i+1)/TTJetsSL.GetBinContent(i+1))
    hs=THStack()
    hs.Add(QCDBkgSR);
    hs.Add(TTJetsBkgSR)
    hs.Add(ZInvBkgSR)
    Total=hs.GetStack().Last()
    for i in range(0,Total.GetNbinsX()):
        if i%20 is 0 :Total.GetXaxis().SetBinLabel(i+1,"%d" %i)
        else: Total.GetXaxis().SetBinLabel(i+1,"");
    Total.GetYaxis().SetTitle("Yields %2.1f/fb" % (lumi/1000.)); #Convert pb-1 to fb-1
    Total.GetYaxis().SetRangeUser(0.01,10000000);
    c1 = TCanvas( 'c1', 'StackPlot', 1600,800 )
    c1.SetLogy(); 
    Total.SetLineColor(kBlack);
    Total.SetLineWidth(3);
    Total.Draw("");
    for i in range(0, Total.GetNbinsX()):print Total.GetBinContent(i+1), Total.GetBinError(i+1)
    hs.Draw("hist")
    Total.SetFillStyle(3001);
    Total.SetFillColor(kBlack);
    #Total.Draw("e2same");
    c1.Print("TestStack.pdf");
    output.cd();
    GJetsYields.Write("GJetsControl");
    DYYields.Write("DYControl");
    TFDY.Write("TFDY");
    TFLowDphi.Write("TFLowDphi");
    LDPYields.Write("LDPControl");
    TTJetsSL.Write("SLControl");
    TFSingleLepton.Write("TFSingleLepton");
    ZInvBkgSR.Write("ZInvBkgSR");
    QCDBkgSR.Write("QCDBkgSR");
    TTJetsBkgSR.Write("SLBkgSR");

if __name__ == "__main__":
    '''
    Example of how to run:
    python QuickBkgSystematics.py
    '''

    # Read parameters
    parser = argparse.ArgumentParser(description='Run MakeAllDCsyst.C in a loop for all mass points.')
    parser.add_argument("-i", "--indir",      default="datacards_syst/",             help="The EOS directory storing the input skim (default = %(default)s)")
    parser.add_argument("-l", "--luminosity", default=35900.,            type=float, help="The liminosity to scale the backgrounds to in pb-1 (default = %(default)s)")
    parser.add_argument("-o", "--outdir",     default="datacards_syst/",             help="Output folder (default = %(default)s)")
    parser.add_argument("-s", "--suffix",     default="",                            help="Suffix to append to the output file (default = %(default)s)")
    
    args, unknown = parser.parse_known_args()

    hadd_if_necessary(args.indir,"SL")
    hadd_if_necessary(args.indir,"DY_CleanVars")
    make_bkg_systematics(args.indir, args.outdir, args.suffix, args.luminosity)
