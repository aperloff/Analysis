from ROOT import *
import os
ftemp=open("card_template.txt", "r");
fsig=TFile("RA2bin_signal_T1tttt_2000_100.root", "READ");
Signal=fsig.Get("RA2bin_T1tttt_2000_100_fast_nominal")
Signal.Scale(35900.);
fbkg=TFile("BkgInputCards.root")
SLControlYields=fbkg.Get("SLControl");
SLControlTF=fbkg.Get("TFSingleLepton");

ZInv=fbkg.Get("ZInvBkgSR");
QCD=fbkg.Get("QCDBkgSR");
LostLepton=fbkg.Get("SLBkgSR");
GJControl=fbkg.Get("GJControl");
GJTF=fbkg.Get("TFGJ")
bincount=174;
cardsToCombine=" "
for i in range(1, ZInv.GetNbinsX()+1):
	fout=open("card_searchbin%d.txt" %i, 'w')
	fout.seek(0)
	cardsToCombine=cardsToCombine+"card_searchbin%d.txt " %i
	TotalBkg=ZInv.GetBinContent(i)+QCD.GetBinContent(i)+LostLepton.GetBinContent(i);
	Sig=Signal.GetBinContent(i)
	ftemp.seek(0);
	for line in ftemp:
		newline=line
		if "OBS" in line: newline=line.replace("OBS", "%2.2f" %TotalBkg )
		if "rate" in line:
			newline=line.replace("SIG", "%2.2f" %Sig);
			newline=newline.replace("SL", "%2.2f" %LostLepton.GetBinContent(i))
			newline=newline.replace("Z", "%2.2f" %ZInv.GetBinContent(i))
			newline=newline.replace("Q", "%2.2f" %QCD.GetBinContent(i))
		fout.write(newline);
	#NOW NUISANCES:	
	
	fout.write("QCDUnc lnN - - - 1.4 \n")
	if(SLControlYields.GetBinContent(i)>0):fout.write("LLLepStat_%d lnN - %2.2f - - \n" %(i,1.0+SLControlYields.GetBinError(i)/SLControlYields.GetBinContent(i)))
	else:fout.write("LLLepStat_%d gmN 0 - %2.2f - - \n" %(i,SLControlTF.GetBinContent(i)))
	if GJControl.GetBinContent(i)>0:fout.write("GJStat_%d lnN - - %2.2f - - \n" %(i, 1.0+GJControl.GetBinError(i)/GJControl.GetBinContent(i)));
	else: fout.write("GJStat_%d gmN 0 - - %2.2f - - \n" %(i,GJTF.GetBinContent(i)))	
	fout.close()
os.system("combineCards.py %s >combinedBinTest.txt " %cardsToCombine)
os.system("combine -M Asymptotic combinedBinTest.txt -n T1tttt_2000_100 " )	
