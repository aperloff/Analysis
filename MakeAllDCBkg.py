import os, errno, argparse
import ROOT

if __name__ == "__main__":
	'''
	Example of how to run:
	python MakeAllDCBkg.py

	root -b -l -q 'MakeAllDCBkg.C+(0,"signal","TotalBkg","root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12","nominal","")'
	'''

	# Read parameters
	parser = argparse.ArgumentParser(description='Run MakeAllDCsyst.C in a loop for all mass points.')
	parser.add_argument("-c", "--count",     default=False,      action="store_true", help="Simply count the number of jobs (default = %(default)s)")
	parser.add_argument("-i", "--indir",     default="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/", help="The EOS directory storing the input skim (default = %(default)s)")
	parser.add_argument("-m", "--mode",      default=0,                               help="The mode, where 1=fastsim (default = %(default)s)")
	parser.add_argument("-n", "--npool",     default=8,                               help="The number of processes to run (default = %(default)s)")
	parser.add_argument("-o", "--outdir",    default="datacards_syst",                help="Output folder (default = %(default)s)")
	parser.add_argument("-r", "--region",    default=["signal"], nargs='+',           help="The signal or control regions to run (default = %(default)s)")
	parser.add_argument("-s", "--setname",   default="TotalBkg",                      help="The modle to scan (default = %(default)s)")
	parser.add_argument(      "--systTypes", default="nominal,scaleuncUp,scaleuncDown,isruncUp,isruncDown,triguncUp,triguncDown,btagSFuncUp,btagSFuncDown,mistagSFuncUp,mistagSFuncDown,isotrackuncUp,isotrackuncDown,lumiuncUp,lumiuncDown", help="")
	parser.add_argument("-v", "--varTypes",  default="JECup,JECdown,JERup,JERdown",   help="")
	
	args, unknown = parser.parse_known_args()

	ROOT.gInterpreter.ProcessLine("#include \"KPlotDriver.C\"")
	ROOT.gErrorIgnoreLevel = ROOT.kBreak

	if args.mode == -1:
		print "Recompiled MakeAllDCsyst, exiting."
		exit(-1);
	
	if args.indir[-1] != '/':
		indir = indir + "/"
	inpre = "tree_"
	outpre = "RA2bin_"
	input = "input/input_RA2bin_DC_systbkg.txt"
	setlist = ""
	osuff = ""

	#process variaton types - comma-separated input, need to be run separately
	vars = args.varTypes.split(',')
	
	if mode == 1:
		outdir = "datacards_fast/"
		setlist = "input/fast/input_set_DC_"+setname+".txt"
		osuff = "_"+setname
	else:
		outdir = "datacards_syst/"
		setlist = "input/input_sets_DC_v2.txt"
		osuff = "_"+setname

	#check for directory
	if len(outdir) > 0 and not os.path.isdir(outdir):
		try:
		    os.makedirs(directory)
		except OSError as e:
		    if e.errno != errno.EEXIST:
		        raise


	
	#keep a list of root files
	rootfiles = []
	
	#do the simple systematics all at once
	rootfiles.append(outdir+outpre+region+osuff);
	ROOT.KPlotDriver(indir+inpre+region,{input,setlist},{"OPTION","string:rootfile["+rootfiles.back()+"]","vstring:selections["+systTypes+"]"});


