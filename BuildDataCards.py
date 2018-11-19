from ROOT import *
import os, bisect, argparse, subprocess, shlex
from multiprocessing import Pool
from math import sqrt

ZinvStatDict = [
    (10, 1.10),
    (20, 1.10),
    (30, 1.35),
    (40, 1.10),
    (50, 1.10),
    (60, 1.20),
    (70, 1.50),
    (80, 1.10),
    (90, 1.10),
    (100, 1.30),
    (110, 1.50),
    (118, 1.10),
    (126, 1.20),
    (174, 1.50),

]
ZinvStatDict.sort() # list must be sorted
ZinvStatLumiValue = 35900.0 # Luminosity at which these values were measured

def which(program):
    def is_exe(fpath):
        return os.path.isfile(fpath) and os.access(fpath, os.X_OK)

    fpath, fname = os.path.split(program)
    if fpath:
        if is_exe(program):
            return program
    else:
        for path in os.environ["PATH"].split(os.pathsep):
            exe_file = os.path.join(path, program)
            if is_exe(exe_file):
                return exe_file

    return None

def BuildDataCards(options_model_mass):
    indir_sig = options_model_mass[0]
    indir_bkg = options_model_mass[1]
    luminosity = options_model_mass[2]
    suffix = options_model_mass[3]
    outdir = options_model_mass[5]
    if not os.path.exists(outdir):
        os.makedirs(outdir)

    ftemp=open("card_template.txt", "r");
    fsig=TFile(indir_sig+"RA2bin_signal_"+options_model_mass[6]+"_fast.root", "READ");
    Signal=fsig.Get("RA2bin_"+options_model_mass[6]+"_fast_nominal")
    Signal.Scale(luminosity);
    fbkg=TFile(indir_bkg+"BkgInputCards"+suffix+".root")
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
        fout=open(outdir+"card_searchbin%d.txt" %i, 'w')
        fout.seek(0)
        cardsToCombine=cardsToCombine+outdir+"card_searchbin%d.txt " %i
        TotalBkg=ZInv.GetBinContent(i)+QCD.GetBinContent(i)+LostLepton.GetBinContent(i);
        Sig=Signal.GetBinContent(i)
        ftemp.seek(0);
        for line in ftemp:
            newline=line
            if "OBS" in line: newline=line.replace("OBS", "%2.2f" %TotalBkg )
            if "rate" in line:
                newline=line.replace("SIG", "%2.2f" %Sig);
                newline=newline.replace("SL", "%2.2f" % (LostLepton.GetBinContent(i) if LostLepton.GetBinContent(i)>0.01 else 0.01))
                newline=newline.replace("Z", "%2.2f" % (ZInv.GetBinContent(i) if ZInv.GetBinContent(i)>0.01 else 0.01))
                newline=newline.replace("Q", "%2.2f" % (QCD.GetBinContent(i) if QCD.GetBinContent(i)>0.01 else 0.01))
            fout.write(newline);
        #NOW NUISANCES: 
    
        fout.write("QCDUnc lnN - - - 1.4 \n")
        if(SLControlYields.GetBinContent(i)>0):fout.write("LLLepStat_%d lnN - %2.2f - - \n" %(i,1.0+SLControlYields.GetBinError(i)/SLControlYields.GetBinContent(i)))
        else:fout.write("LLLepStat_%d gmN 0 - %2.2f - - \n" %(i,SLControlTF.GetBinContent(i)))
        if luminosity != ZinvStatLumiValue:
            ZinvStatUnc = 1.0+((ZinvStatDict[bisect.bisect_right(ZinvStatDict, (i,))][1] - 1.0) * sqrt(ZinvStatLumiValue/luminosity))
        else:
            ZinvStatUnc = ZinvStatDict[bisect.bisect_right(ZinvStatDict, (i,))][1]
        fout.write("ZinvStat_%d lnN - - %2.2f - \n" %(i,ZinvStatUnc)) #Estimation based on Figure 40 in AN-2016/350
        
        #if GJControl.GetBinContent(i)>0:fout.write("GJStat_%d lnN - - %2.2f - - \n" %(i, 1.0+GJControl.GetBinError(i)/GJControl.GetBinContent(i)));
        #else: fout.write("GJStat_%d gmN 0 - - %2.2f - - \n" %(i,GJTF.GetBinContent(i)))    
        fout.close()
    return cardsToCombine

def ProcessModelMass(options_model_mass):
    print "Processing " + options_model_mass[6] + " ..."
    cardsToCombine = BuildDataCards(options_model_mass)
    if which("combineCards.py") != None:
        os.system("combineCards.py %s > %scombinedBinTest.txt " % (cardsToCombine,options_model_mass[5]))
    else:
        print "ERROR can't find combineCards.py!"

    if options_model_mass[4] and which("combine") != None:
        combine_file = "higgsCombine"+options_model_mass[6]+".AsymptoticLimits.mH120.root"
        out=open(options_model_mass[5]+combine_file[:-5]+".stdout","w")
        cmd = "combine -M AsymptoticLimits "+options_model_mass[5]+"combinedBinTest.txt -n "+options_model_mass[6]
        proc = subprocess.Popen(shlex.split(cmd), shell=False, stdout=out, stderr=subprocess.STDOUT)
        proc.wait()
        stdout,stderr=proc.communicate()
        if stderr:
            out.write("Model/mass point " + options_model_mass[6] + " had an ERROR")
        else:
            out.write("Model/mass point " + options_model_mass[6] + " completed successfully")
        out.close()
        os.system("mv "+combine_file+" "+options_model_mass[5]+combine_file)

if __name__ == "__main__":
    '''
    Examples of how to run:
    python BuildDataCards.py -l 35900.0 -m T1qqqq T1qqqq T2tt T2tt T2qq T2qq --mass 1900_100 1300_1200 1100_50 600_500 1500_100 1100_900 -o datacards/lumi2016/ -s _35900pb-1 -r

    Print limits using:
    for x in T1qqqq_1900_100 T1qqqq_1300_1200 T2tt_1100_50 T2tt_600_500 T2qq_1500_100 T2qq_1100_900; do tail -n 7 datacards/lumi2016/${x}_fast/higgsCombine${x}.AsymptoticLimits.mH120.stdout; done
    '''

    # Read parameters
    parser = argparse.ArgumentParser(description='Build datacards and run combine for multiple models and mass points.')
    parser.add_argument("-i", "--indir_sig",  default="datacards_fast/",             help="The directory containing the signal histograms (default = %(default)s)")
    parser.add_argument("-j", "--indir_bkg",  default="datacards_syst/",             help="The directory containing the background histograms (default = %(default)s)")
    parser.add_argument("-l", "--luminosity", default=35900.,            type=float, help="The liminosity to scale the backgrounds to in pb-1 (default = %(default)s)")
    parser.add_argument(      "--list",       action="store_true",                   help="List the model+mass points and their parameters (default = %(default)s)")
    parser.add_argument("-m", "--model",      default=["T1tttt"],        nargs='+',  help="The signal model (default = %(default)s)")
    parser.add_argument(      "--mass",       default=["2100_100"],      nargs='+',  help="The gluino and neutralino masses (default = %(default)s)")
    parser.add_argument("-n", "--npool",      default=8,                             help="The number of processes to run (default = %(default)s)")
    parser.add_argument("-o", "--outdir",     default="datacards/",                  help="Output folder (default = %(default)s)")
    parser.add_argument("-r", "--run",        action="store_true",                   help="Run the combine tool to calculate the limits (default = %(default)s)")
    parser.add_argument("-s", "--suffix",     default="",                            help="The suffix appended to the file containing the background histograms (default = %(default)s)")
    
    args, unknown = parser.parse_known_args()

    #common list of options
    optlist = [args.indir_sig, args.indir_bkg, args.luminosity, args.suffix, args.run]
    options_model_mass = [optlist + [args.outdir+x+"_"+args.mass[ix]+"_fast/",x+"_"+args.mass[ix]] for ix, x in enumerate(args.model)]

    #list the models/mass points which will be run
    if args.list:
        print "Will process "+str(len(options_model_mass))+" models/mass points:\n"
        for x in options_model_mass:
            print x[6]+":"
            print "\tSignal Location:",x[0]
            print "\tBackground Location:",x[1]
            print "\tLuminosity:",x[2]
            print "\tBackground Suffix:",x[3]
            print "\tRun Combine:",x[4]
            print "\tOutput Directory:",x[5]+"\n"
        exit(0)

    p = Pool(int(args.npool))
    p.map(ProcessModelMass,options_model_mass)
