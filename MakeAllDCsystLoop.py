#!/usr/bin/env python
import argparse, glob, os, subprocess, shlex
from multiprocessing import Pool

def doMassPoint(optlist):
	mode = optlist[0]
	indir = optlist[1]
	outdir = optlist[2]
	name = optlist[3]

	cmd='root -b -l -q '
	cmd += """'MakeAllDCsyst.C+("""+str(args.mode)+',\"'+name+'\",\"'+indir+'\",\"'+outdir+"""")'"""
	out=open("RA2bin_proc_"+name+".stdout","w")
	proc = subprocess.Popen(shlex.split(cmd), shell=False, stdout=out, stderr=subprocess.STDOUT)
	proc.wait()
	stdout,stderr=proc.communicate()
	if stderr:
		print "Mass point",name,"had an ERROR"
	else:
		print "Mass point",name,"completed successfully"
	out.close()

if __name__ == "__main__":
	'''
	Example of how to run:
	python MakeAllDCsystLoop.py

	root -b -l -q 'MakeAllDCsyst.C+(1,"T1tttt_900_1_fast","root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan")'
	'''

	# Read parameters
	parser = argparse.ArgumentParser(description='Run MakeAllDCsyst.C in a loop for all mass points.')
	parser.add_argument("-c", "--count",   action="store_true",                   help="Simply count the number of jobs (default = %(default)s)")
	parser.add_argument("-d", "--debug",   action="store_true",                   help="Print debugging information (default = %(default)s)")
	parser.add_argument("-i", "--indir",   default="root://cmseos.fnal.gov//store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV12/scan", help="The EOS directory storing the input skim (default = %(default)s)")
	parser.add_argument("-m", "--mode",    default=1,                             help="The mode, where 1=fastsim (default = %(default)s)")
	parser.add_argument(      "--mass",    default=[],                nargs='+',  help="The gluino and neutralino masses (default = %(default)s)")
	parser.add_argument("-n", "--npool",   default=8,                             help="The number of processes to run (default = %(default)s)")
	parser.add_argument("-o", "--outdir",  default="datacards_fast/",             help="Output folder (default = %(default)s)")
	parser.add_argument("-s", "--setname", default=["T1tttt"],        nargs='+',  help="The model(s) to scan (default = %(default)s)")
	
	args, unknown = parser.parse_known_args()
	
	if len(args.mass)==0:
		mass_point_files = []
		for setname in args.setname:
			mass_point_files += [os.path.split(x)[1] for x in glob.glob("input/fast/*") if setname in x]
		mass_points = [x.split("_")[3]+"_"+x.split("_")[4]+"_"+x.split("_")[5]+"_"+x.split("_")[6].split(".")[0] for x in mass_point_files]
	else:
		mass_points = [args.setname[ix]+"_"+x+"_fast" for ix, x in enumerate(args.mass)]

	if args.count:
		print "Need to process",len(mass_points),"jobs"
		if args.debug:
			for mp in mass_points:
				print "\t"+mp
		exit(0)


	#common list of options
	optlist = [args.mode, args.indir, args.outdir]
	mass_point_options = [optlist + [x] for x in mass_points]

	p = Pool(int(args.npool))
	p.map(doMassPoint,mass_point_options)
