import sys, os, stat
from optparse import OptionParser
import imp

def makeSkimLine(short_name,full_names,file_mins,file_maxs,mothers,btype="skim",block=-1,data=False):
    the_name = short_name + ("_block"+str(block) if block >= 0 else "")
    line = "base" + "\t" + btype + "\t" + the_name + ("\t" + "u:block[" + str(block) + "]" if block >= 0 else "") + "\t" + "b:chain[1]" + "\t"
    line += "ch:filenames[" + str(','.join(full_names[i]+"_,"+str(file_mins[i])+","+str(file_maxs[i])+","+"_RA2AnalysisTree.root" for i, x in enumerate(full_names))) + "]" + "\t" 
    line += "s:chainsuff[/TreeMaker2/PreSelection]" + ("\t"+"vi:mother["+str(','.join(str(m) for m in mothers))+"]" if len(mothers) > 0 else "") + ("\t"+"b:data[1]" if data else "\t"+"b:data[0]") + "\n"
    expline = the_name + " \\\n"
    return (line,expline)

def makeSkimInput(read,write,export,btype="skim",nfiles=0,data=False,folder="",nfilesTM=1,preamble=""):
    readname = read.replace(".py","").split("/")[-1]
    rfile = imp.load_source(readname,read)
    wfile = open(write,'w')
    efile = open(export,'w')

    # preamble for file
    if len(preamble)>0: wfile.write(preamble+"\n")
    wfile.write("SET\n")
    
    # preamble for script to export array of sample names
    efile.write("#!/bin/bash\n")
    efile.write("\n")
    efile.write("export SAMPLES=(\n")

    totfiles = 0
    totjobs = 0
    for rline in rfile.flist:
        full_names = rline[0]
        file_lens = []
        file_mins = []
        file_maxs = []
        #lists of file indices and part numbers
        indices = []
        pnumbers = []
        short_name = rline[1][0]
        mother = []
        if len(rline[1])>1: mother = rline[1][1:]
        
        for ind, full_name in enumerate(full_names):
            # account for skipped runs in prompt reco
            if data and "PromptReco" in full_name and len(folder)>0:
                fileArrays = filter(None,os.popen("xrdfs root://cmseos.fnal.gov/ ls "+folder+" | grep \""+full_name+"\"").read().split('\n'))
                # get part numbers of existing ntuples: name format is ...._X_RA2AnalysisTree.root
                ptmp = [ int(f.split('_')[-2]) for f in fileArrays ]
                ptmp.sort()
                
                #make list of file indices and part numbers
                fileListLen = len(ptmp)
                indices.extend([ind]*fileListLen)
                pnumbers.extend(ptmp)
                
                file_lens.append(fileListLen)
                file_mins.append(ptmp[0])
                file_maxs.append(ptmp[-1])
                totfiles += fileListLen
            else:
                readFilesImport = getattr(__import__("TreeMaker.Production." + full_name + "_cff",fromlist=["readFiles"]),"readFiles")
                fileListLen = len(readFilesImport)
                if nfilesTM==-1:
                    nJobs = 1
                else:
                    nJobs = fileListLen / int(nfilesTM)
                    if fileListLen % int(nfilesTM) != 0:
                        nJobs += 1
                file_lens.append(nJobs)
                file_mins.append(0)
                file_maxs.append(nJobs-1)
                totfiles += nJobs
        
        # check for splitting into blocks
        fileListLen = sum(file_lens)
        nblocks = 0
        if nfiles>0: nblocks = fileListLen/nfiles + int(fileListLen%nfiles!=0)
        
        if nblocks<2: # all files in one chain (either no splitting or nfiles < fileListLen)
            wline,eline = makeSkimLine(short_name,full_names,file_mins,file_maxs,mother,btype,-1,data)
            wfile.write(wline)
            efile.write(eline)
        else: # split chains into several blocks
            # make list of file indices and part numbers
            for ind, full_name in enumerate(full_names):
                if data and "PromptReco" in full_name and len(folder)>0: continue # already done for prompt data
                indices.extend([ind]*file_lens[ind])
                pnumbers.extend(range(0,file_lens[ind]))
        
            for block in range(0,nblocks):
                fileMin = block*nfiles
                fileMax = min((block+1)*nfiles-1,fileListLen-1)
                # check lists
                indexMin = indices[fileMin]
                indexMax = indices[fileMax]
                pnumberMin = pnumbers[fileMin]
                pnumberMax = pnumbers[fileMax]
                # check for crossover between two samples
                if indexMin == indexMax: wline,eline = makeSkimLine(short_name,[full_names[indexMin]],[pnumberMin],[pnumberMax],mother,btype,block,data)
                else: wline,eline = makeSkimLine(short_name,[full_names[indexMin],full_names[indexMax]],[pnumberMin,0],[file_lens[indexMin]-1,pnumberMax],mother,btype,block,data)
                wfile.write(wline)
                efile.write(eline)
        print short_name + " : nfiles = " + str(fileListLen) + ", njobs = " + str(max(nblocks,1))
        totjobs += max(nblocks,1)
    print "total nfiles = " + str(totfiles) + ", total njobs = " + str(totjobs)
    
    # make the script executable
    st = os.stat(efile.name)
    os.chmod(efile.name, st.st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)

    # close files
    wfile.close()
    efile.write(")\n")
    efile.close()
    
#####################################################################################################################

if __name__ == "__main__":
    # define options
    parser = OptionParser()
    parser.add_option("-r", "--read", dest="read", default="input/dict_skim.txt", help="input file to read")
    parser.add_option("-w", "--write", dest="write", default="input/input_sets_skim.txt", help="output file to write")
    parser.add_option("-e", "--export", dest="export", default="batch/exportSkim.sh", help="export file to write")
    parser.add_option("-n", "--nfiles", dest="nfiles", default=0, help="number of files per block for skim input")
    parser.add_option("-N", "--nfilesTM", dest="nfilesTM", default=1, help="number of files per ntuple (from TreeMaker)")
    parser.add_option("-d", "--data", dest="data", default=False, action="store_true", help="denotes data file (instead of MC)")
    parser.add_option("-f", "--folder", dest="folder", default="", help="EOS directory to check for data ntuples")
    (options, args) = parser.parse_args()

    makeSkimInput(options.read,options.write,options.export,"skim",int(options.nfiles),options.data,options.folder,options.nfilesTM)
