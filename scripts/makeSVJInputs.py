import os
from argparse import ArgumentParser
from collections import OrderedDict

def parse(sample):
    params = {}
    samplesplit = sample.split("_")
    for s in samplesplit:
        if "-" in s:
            kv = s.split("-")
            params[kv[0]] = kv[1]

    return params

# define options
parser = ArgumentParser()
parser.add_argument("-d", "--dir", dest="dir", default="/store/user/lpcsusyhad/SVJ2017/Run2ProductionV16/Skims/tree_dijetmtdetahadmf/", help="location of root files (LFN)")
args = parser.parse_args()

# find the root files
files = filter(None,os.popen("xrdfs root://cmseos.fnal.gov/ ls "+args.dir).read().split('\n'))
# basename
files = [ f.split("/")[-1] for f in files]
files = [x for x in files if "SVJ" in x]

# style
colors = ["kBlack","kBlue","kMagenta + 2","kRed","kCyan + 2","kMagenta","kOrange + 7","kYellow + 3","kGreen + 2","kPink - 9","kGray + 1"]
styles = [1,2,3,4,7,9]
cc = 0
cs = 0

# alpha val translation
alphavals = {
    "high": -1,
    "peak": -2,
    "low": -3,
}

# default params
params_default = OrderedDict([
    ("mZprime", 3000),
    ("mDark", 20),
    ("rinv", 0.3),
    ("alpha", "peak"),
])

# open files
dfile = open("input/input_svj_hp_sets_sig.txt",'w')
sfile = open("input/input_svj_sets_sig.txt",'w')
sfile.write("SET\n")
ifile = open("input/input_svj_train_options.txt",'w')
numers = []
branches = []
for sample in files:
    # parse filename: tree_SVJ_mZprime-1000_mDark-20_rinv-0.3_alpha-peak_MC2017.root
    params = parse(sample)
    name = sample.replace("tree_","").replace(".root","")
    # make short name
    sname = "SVJ"+"_"+str(params["mZprime"])+"_"+str(params["mDark"])+"_"+str(params["rinv"])+"_"+str(params["alpha"])
    year = "MC2017" if "MC2017" in sample else "MC2016"
    # make flat branch name
    found_nondefault = False
    for p in params_default:
        pv = params[p]
        if str(params_default[p]) != str(pv):
            if p=="mZprime": branches.append("Z"+str(int(float(pv)/100)))
            elif p=="mDark": branches.append("D"+str(pv))
            elif p=="rinv": branches.append("R"+str(int(float(pv)*10)))
            elif p=="alpha":
                pv2 = "Pk" if pv=="peak" else "Hi" if pv=="high" else "Lo" if pv=="low" else str(int(float(pv)*10))
                branches.append("A"+pv2)
            found_nondefault = True
            break
    if not found_nondefault: # default
        branches.append("Z"+str(int(float(params["mZprime"])/100)))
    # make lines
    dline1 = "\t".join(["hist", "mc", sname+"_"+year, "s:legname["+sname+"]","c:color["+colors[cc]+"]","i:linestyle["+str(styles[cs])+"]"])
    alphaval = alphavals[params["alpha"]] if params["alpha"] in alphavals else params["alpha"]
    plines = ["d:mZprime["+str(params["mZprime"])+"]","d:mDark["+str(params["mDark"])+"]","d:rinv["+str(params["rinv"])+"]","d:alpha["+str(alphaval)+"]"]
    dline2 = "\t".join(["", "base", "mc", sname+"_"+year, "s:filename["+sample+"]"] + plines)
    dfile.write(dline1+"\n")
    dfile.write(dline2+"\n")
    # make skim line
    sline = "\t".join(["base", "skim", name, "s:filename["+sample+"]","b:data[0]","s:flatsuff["+sname+"_"+year+"]"] + plines)
    sfile.write(sline+"\n")
    # append to training lines
    numers.append(sname+"_"+year)
    
    # increment style counters
    cc += 1
    if cc>=len(colors):
        cc = 0
        cs += 1
        if cs>=len(styles):
            cs = 0

# write options
ifile.write("vs:flatnumers["+",".join(numers)+"]"+"\n")
ifile.write("vs:flatbranches["+",".join(branches)+"]"+"\n")
