from ROOT import *
import math
fin=TFile("RA2bin_signal_TotalBkg.root", "READ")
#4 main RA2 bkgs
TTJetsBkgSR=fin.Get("RA2bin_TTJets_nominal")
WJetBkgSR=fin.Get("RA2bin_WJet_nominal")
ZInvBkgSR=fin.Get("RA2bin_ZInv_nominal")
QCDBkgSR=fin.Get("RA2bin_QCD_nominal")

# Control Regions
finSL=TFile("RA2bin_SL_TotalBkg.root", "READ");
TTJetsSL=finSL.Get("RA2bin_TTJets_nominal");
WJetsSL=finSL.Get("RA2bin_WJet_nominal");
TTJetsSL.Add(WJetsSL); #Total Single Lepton
output=TFile("BkgInputCards.root","RECREATE");
TFSingleLepton=TTJetsBkgSR.Clone("TFSingleLepton")
TFSingleLepton.Reset();
TFLowDphi=QCDBkgSR.Clone("TFLowDphi")
TFLowDphi.Reset();
TFGJ=ZInvBkgSR.Clone("TFGJ")
TFGJ.Reset();
TTJetsSL.Scale(35900.)
ZInvBkgSR.Scale(35900)
WJetBkgSR.Scale(35900)
TTJetsBkgSR.Scale(35900)
QCDBkgSR.Scale(35900)

for i in range(0,TTJetsSL.GetNbinsX()):
	TF=(TTJetsBkgSR.GetBinContent(i+1)+WJetBkgSR.GetBinContent(i+1))/TTJetsSL.GetBinContent(i+1)
	TFSingleLepton.SetBinContent(i+1,TF);
	#print "TF 0L/1L %g " %TF
	if TTJetsSL.GetBinContent(i+1)>1: 
		TTJetsSL.SetBinError(i+1, math.sqrt(TTJetsSL.GetBinContent(i+1)));
	else:
		TTJetsSL.SetBinError(i+1, TF);
		TTJetsSL.SetBinContent(i+1, 0.0) #use gamma function for less than 2 events
		
finLDP=TFile("RA2bin_LDP_TotalBkg.root", "READ");
LDPYields=finLDP.Get("RA2bin_QCD_nominal") #Low DPhi Yields 
LDPYields.Scale(35900.);
for i in range(0,LDPYields.GetNbinsX()):
	TF=1.0;
	if(LDPYields.GetBinContent(i+1)>0):TF=QCDBkgSR.GetBinContent(i+1)/LDPYields.GetBinContent(i+1);		
	TFLowDphi.SetBinContent(i+1, TF);
        if LDPYields.GetBinContent(i+1)>1: 
                LDPYields.SetBinError(i+1, math.sqrt(LDPYields.GetBinContent(i+1)));
	else:
		LDPYields.SetBinError(i+1,TF);
		LDPYields.SetBinContent(i+1,0)	


finGJets=TFile("RA2bin_GJet_CleanVars_TotalBkg.root","READ");
finDY=TFile("RA2bin_DY_CleanVars_TotalBkg.root","READ");
DYYields=finDY.Get("RA2bin_DY_nominal");
DYYields.Scale(35900);
GJYields=finGJets.Get("RA2bin_GJets_nominal");
GJYields.Scale(35900)
for i in range(0,GJYields.GetNbinsX()):
	TF=1.0;
	if(GJYields.GetBinContent(i+1)>0):TF=ZInvBkgSR.GetBinContent(i+1)/GJYields.GetBinContent(i+1);		
	print TF
	TFGJ.SetBinContent(i+1, TF);
        if GJYields.GetBinContent(i+1)>1: 
                GJYields.SetBinError(i+1, math.sqrt(GJYields.GetBinContent(i+1)));
	else:
		GJYields.SetBinError(i+1,TF);
		GJYields.SetBinContent(i+1,0)	

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
Total.GetYaxis().SetTitle("Yields 35.9/fb");
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
GJYields.Write("GJControl");
TFGJ.Write("TFGJ");
TFLowDphi.Write("TFLowDphi");
LDPYields.Write("LDPControl");
TTJetsSL.Write("SLControl");
TFSingleLepton.Write("TFSingleLepton");
ZInvBkgSR.Write("ZInvBkgSR");
QCDBkgSR.Write("QCDBkgSR");
TTJetsBkgSR.Write("SLBkgSR");
