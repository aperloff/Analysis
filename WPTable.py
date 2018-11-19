#from ROOT import *
from collections import defaultdict
from DefaultOrderedDict import *
import glob, argparse, json
import pandas as pd

#From: https://stackoverflow.com/questions/29986185/python-argparse-dict-arg
class StoreDictKeyPair(argparse.Action):
     def __init__(self, option_strings, dest, nargs=None, **kwargs):
         self._nargs = nargs
         super(StoreDictKeyPair, self).__init__(option_strings, dest, nargs=nargs, **kwargs)
     def __call__(self, parser, namespace, values, option_string=None):
         my_dict = {}
         #print "values: {}".format(values)
         for kv in values:
             k,v = kv.split("=")
             my_dict[k] = v
         setattr(namespace, self.dest, my_dict)

def FormModelMassDict(models, masses):
    '''
    d = FormModelMassDict(['T1tttt','T1tttt','T2tt'],['2100_100','1600_1200','600_500'])
    '''
    #d = defaultdict(list)
    d = DefaultOrderedDict(list)
    for imodel, model in enumerate(models):
        d[model].append(masses[imodel])
    return d

def MakeXSecDict(file):
    d = {}
    with open(file) as f:
        for line in f:
           (key, val) = line.split()
           d[int(key)] = val
    return d

def MakeDataframe(column_dict, indices):
    # df = pd.DataFrame({'WP1' : [1,2], 'WP2' : [3,4]}, index=['T1tttt','T1qqqq'])
    return pd.DataFrame(column_dict, index=indices)

def MakeTable(df):
    latex_table = df.round(4).to_latex().replace('toprule','hline').replace('midrule','hline') \
                                        .replace('bottomrule','hline').replace('lrr','|l|c|c|') \
                                        .replace('{}','\\textbf{Model}').replace('WP1','\\textbf{WP1}') \
                                        .replace('WP2','\\textbf{WP2}')
    index = latex_table.find('\hline')
    latex_table = latex_table[:index] + '\hline\n{} & \multicolumn{2}{c|}{\\textbf{Mass Point}} \\\\\n' + latex_table[index:]
    return latex_table

def WPTable2016(model_mass_dict, args):
    convert = True if args.sig and not args.xsec else False

    column_dict = DefaultOrderedDict(list,{'WP1': [], 'WP2' : []})
    for model,masses in model_mass_dict.iteritems():
        xsec_dict = MakeXSecDict(args.xsec_dict[model])
        file = TFile(glob.glob('%s/CMS-SUS-16-033_Figure_???-?-%s.root' % (args.indir,model))[0],"READ")
        MassScan2DExp = file.Get('MassScan2DExp')
        for imass, mass in enumerate(masses):
            x_mass, y_mass = [float(x) for x in mass.split("_")]
            bin = MassScan2DExp.FindBin(x_mass,y_mass)
            xsec_pb = MassScan2DExp.GetBinContent(bin)
            value = xsec_pb if not convert else xsec_pb/float(xsec_dict[x_mass])
            column_dict[list(column_dict)[imass]].append(value)

            if args.debug:
                print "Model:",model
                print "Mass Point:", mass
                print "\t(x_mass,y_mass): ("+str(x_mass)+","+str(y_mass)+")"
                print "Bin:", bin
                print "Cross Section Limit [pb]:",str(xsec_pb)
                print "Value (converted):",str(value)+" ("+str(convert)+")"
                if convert: print "Cross Section [pb]:",str(xsec_dict[x_mass])
                print

    df = MakeDataframe(column_dict, list(model_mass_dict))
    table = MakeTable(df)
    return table

def WPTable(args):
    convert = True if args.xsec and not args.sig else False

    column_dict = DefaultOrderedDict(list,{'WP1': [], 'WP2' : []})
    for model,masses in model_mass_dict.iteritems():
        xsec_dict = MakeXSecDict(args.xsec_dict[model])
        for imass, mass in enumerate(masses):
            x_mass, y_mass = [float(x) for x in mass.split("_")]
            file = TFile('%s/%s_%s_fast/higgsCombine%s_%s.AsymptoticLimits.mH120.root' % (args.indir,model,mass,model,mass),"READ")
            limit_tree = file.Get('limit')
            limit_tree.GetEntry(2)
            signal_strength = limit_tree.limit
            value = signal_strength if not convert else signal_strength * float(xsec_dict[x_mass])
            column_dict[list(column_dict)[imass]].append(value)

            if args.debug:
                print "Model:",model
                print "Mass Point:", mass
                print "\t(x_mass,y_mass): ("+str(x_mass)+","+str(y_mass)+")"
                print "50% Expected Limit [pb]:",str(signal_strength)
                print "Value (converted):",str(value)+" ("+str(convert)+")"
                if convert: print "Cross Section [pb]:",str(xsec_dict[x_mass])
                print

    df = MakeDataframe(column_dict, list(model_mass_dict))
    table = MakeTable(df)
    return table

if __name__ == "__main__":
    '''
    Examples of how to run:
    python WPTable.py

    python WPTable.py -i CMS-SUS-16-033/ -M T1tttt T1tttt T1qqqq T1qqqq T2tt T2tt T2qq T2qq \
    -m 2100_100 1600_1200 1900_100 1300_1200 1100_50 600_500 1500_100 1100_900 --result_2016 --sig \
    -d T1tttt=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T1.txt \
    T1qqqq=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T1.txt \
    T2tt=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T2.txt \
    T2qq=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T2qq.txt

    python WPTable.py -i datacards/NominalBinning/lumiRun2/ -M T1tttt T1tttt T1qqqq T1qqqq T2tt T2tt T2qq T2qq -m 2100_100 1600_1200 1900_100 1300_1200 1100_50 600_500 1500_100 1100_900 --combine_result --sig -d T1tttt=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T1.txt T1qqqq=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T1.txt T2tt=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T2.txt T2qq=/uscms_data/d2/aperloff/YOURWORKINGAREA/SUSY/slc7/CMSSW_9_4_10/src/TreeMaker/Production/test/data/dict_xsec_T2qq.txt -D
    '''

    # Read parameters
    parser = argparse.ArgumentParser(description='Make a WPTable.')
    parser.add_argument("-D", "--debug",          action='store_true',                  help="Show extra printouts needed for debugging (default = %(default)s)")
    parser.add_argument("-i", "--indir",          default='CMS-SUS-16-033/',            help="Directory containing the input ROOT files (default = %(default)s)")
    parser.add_argument("-M", "--model",          default=["T1tttt"],        nargs='+', help="The signal model (default = %(default)s)")
    parser.add_argument("-m", "--mass",           default=["2100_100"],      nargs='+', help="The gluino and neutralino masses (default = %(default)s)")
    parser.add_argument("-o", "--output",         default="./WPTable.txt",              help="Output folder (default = %(default)s)")
    result = parser.add_mutually_exclusive_group(required=True)
    result.add_argument(      "--result_2016",    action='store_true',                  help="Form table from 2016 result files (default = %(default)s)")
    result.add_argument("-c", "--combine_result", action='store_true',                  help="Form table from the output of combine (default = %(default)s)")
    method = parser.add_mutually_exclusive_group(required=True)
    method.add_argument("-x", "--xsec",           action='store_true',                  help="Return the result using cross section values (default = %(default)s)")
    method.add_argument("-s", "--sig",            action='store_true',                  help="Return the result using signal strength values (default = %(default)s)")
    #parser.add_argument("-d", "--xsec_dict",      default={},          type=json.loads, help="Dictionary of files containing the model cross sections in case a conversion is needed (default = {%default})")
    parser.add_argument("-d", "--xsec_dict",      action=StoreDictKeyPair,  nargs="+", metavar="KEY=VAL", help="Dictionary of files containing the model cross sections in case a conversion is needed (default = %(default)s)")
    
    args, unknown = parser.parse_known_args()

    from ROOT import *

    assert len(args.model) == len(args.mass)

    model_mass_dict = FormModelMassDict(args.model, args.mass)

    if args.result_2016:
        table = WPTable2016(model_mass_dict, args)
    elif args.combine_result:
        table = WPTable(args)

    print table

    fout = open(args.output,'w')
    fout.write(table)
    fout.close()