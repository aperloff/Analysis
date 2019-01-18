#format for dict entries:
#                            MC: [['sample'] , ['short name']]
#                  MC w/ mother: [['sample'] , ['short name',mother PDGID(s)]]
#         MC w/ extended sample: [['sample','sample_ext'] , ['short name']]
#MC w/ extended sample & mother: [['sample','sample_ext'] , ['short name',mother PDGID(s)]]

flist = [
[['RunIISummer16MiniAODv3.QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],                ['QCD_HT-200to300_MC2016']],
[['RunIISummer16MiniAODv3.QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],                ['QCD_HT-300to500_MC2016']],
[['RunIISummer16MiniAODv3.QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],                ['QCD_HT-500to700_MC2016']],
#[['RunIISummer16MiniAODv3.QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
#  'RunIISummer16MiniAODv3.QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],               ['QCD_HT-700to1000_MC2016']],
[['RunIISummer16MiniAODv3.QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],                    ['QCD_HT-700to1000_MC2016']],
[['RunIISummer16MiniAODv3.QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],              ['QCD_HT-1000to1500_MC2016']],
[['RunIISummer16MiniAODv3.QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],              ['QCD_HT-1500to2000_MC2016']],
[['RunIISummer16MiniAODv3.QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],               ['QCD_HT-2000toInf_MC2016']],
[['RunIISummer16MiniAODv3.WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],        ['WJetsToLNu_HT-70to100_MC2016']],
[['RunIISummer16MiniAODv3.WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],        ['WJetsToLNu_HT-100to200_MC2016']],
[['RunIISummer16MiniAODv3.WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1',
  'RunIISummer16MiniAODv3.WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext2'],        ['WJetsToLNu_HT-200to400_MC2016']],
[['RunIISummer16MiniAODv3.WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],        ['WJetsToLNu_HT-400to600_MC2016']],
[['RunIISummer16MiniAODv3.WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],        ['WJetsToLNu_HT-600to800_MC2016']],
[['RunIISummer16MiniAODv3.WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],       ['WJetsToLNu_HT-800to1200_MC2016']],
[['RunIISummer16MiniAODv3.WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],      ['WJetsToLNu_HT-1200to2500_MC2016']],
[['RunIISummer16MiniAODv3.WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],       ['WJetsToLNu_HT-2500toInf_MC2016']],
[['Summer16.TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],                             ['TTJets_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],        ['TTJets_SingleLeptFromT_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],     ['TTJets_SingleLeptFromTbar_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],                 ['TTJets_DiLept_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_SingleLeptFromT_genMET-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],  ['TTJets_SingleLeptFromT_genMET-150_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_SingleLeptFromTbar_genMET-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],  ['TTJets_SingleLeptFromTbar_genMET-150_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_DiLept_genMET-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],           ['TTJets_DiLept_genMET-150_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],            ['TTJets_HT-600to800_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],           ['TTJets_HT-800to1200_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],          ['TTJets_HT-1200to2500_MC2016']],
[['RunIISummer16MiniAODv3.TTJets_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],           ['TTJets_HT-2500toInf_MC2016']],
[['RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],   ['DYJetsToLL_M-50_HT-100to200_MC2016']],
[['RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],   ['DYJetsToLL_M-50_HT-200to400_MC2016']],
[['RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],   ['DYJetsToLL_M-50_HT-400to600_MC2016']],
[['RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],        ['DYJetsToLL_M-50_HT-600to800_MC2016']],
[['RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],       ['DYJetsToLL_M-50_HT-800to1200_MC2016']],
[['RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],      ['DYJetsToLL_M-50_HT-1200to2500_MC2016']],
[['RunIISummer16MiniAODv3.DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],       ['DYJetsToLL_M-50_HT-2500toInf_MC2016']],
[['RunIISummer16MiniAODv3.DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],               ['DYJetsToLL_M-50_MC2016']],
[['RunIISummer16MiniAODv3.ZJetsToNuNu_HT-100To200_13TeV-madgraph',
  'RunIISummer16MiniAODv3.ZJetsToNuNu_HT-100To200_13TeV-madgraph_ext1'],                               ['ZJetsToNuNu_HT-100to200_MC2016']],
[['RunIISummer16MiniAODv3.ZJetsToNuNu_HT-200To400_13TeV-madgraph',
  'RunIISummer16MiniAODv3.ZJetsToNuNu_HT-200To400_13TeV-madgraph_ext1'],                               ['ZJetsToNuNu_HT-200to400_MC2016']],
[['RunIISummer16MiniAODv3.ZJetsToNuNu_HT-400To600_13TeV-madgraph',
  'RunIISummer16MiniAODv3.ZJetsToNuNu_HT-400To600_13TeV-madgraph_ext1'],                               ['ZJetsToNuNu_HT-400to600_MC2016']],
[['Summer16.ZJetsToNuNu_HT-600To800_13TeV-madgraph'],                                    ['ZJetsToNuNu_HT-600to800_MC2016']],
[['Summer16.ZJetsToNuNu_HT-800To1200_13TeV-madgraph'],                                   ['ZJetsToNuNu_HT-800to1200_MC2016']],
[['Summer16.ZJetsToNuNu_HT-1200To2500_13TeV-madgraph',
  'Summer16.ZJetsToNuNu_HT-1200To2500_13TeV-madgraph_ext1'],                             ['ZJetsToNuNu_HT-1200to2500_MC2016']],
[['Summer16.ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph'],                                   ['ZJetsToNuNu_HT-2500toInf_MC2016']],
[['RunIISummer16MiniAODv3.GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],             ['GJets_HT-100to200_MC2016']],
[['RunIISummer16MiniAODv3.GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],             ['GJets_HT-200to400_MC2016']],
[['RunIISummer16MiniAODv3.GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],             ['GJets_HT-400to600_MC2016']],
[['RunIISummer16MiniAODv3.GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
  'RunIISummer16MiniAODv3.GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext1'],             ['GJets_HT-600toInf_MC2016']],
[['RunIISummer16MiniAODv3.GJets_DR-0p4_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],           ['GJets_DR-0p4_HT-100to200_MC2016']],
[['RunIISummer16MiniAODv3.GJets_DR-0p4_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],           ['GJets_DR-0p4_HT-200to400_MC2016']],
[['RunIISummer16MiniAODv3.GJets_DR-0p4_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],           ['GJets_DR-0p4_HT-400to600_MC2016']],
[['RunIISummer16MiniAODv3.GJets_DR-0p4_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'],           ['GJets_DR-0p4_HT-600toInf_MC2016']],
[['Summer16.ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1'],          ['ST_s-channel_MC2016']],
[['RunIISummer16MiniAODv3.ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1'],        ['ST_t-channel_top_MC2016']],
[['RunIISummer16MiniAODv3.ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1'],    ['ST_t-channel_antitop_MC2016']],
[['RunIISummer16MiniAODv3.ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_ext1'],         ['ST_tW_top_MC2016']],
[['RunIISummer16MiniAODv3.ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_ext1'],     ['ST_tW_antitop_MC2016']],
[['RunIISummer16MiniAODv3.WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph'],                 ['WGJets_MonoPhoton_PtG-40to130_MC2016']],
[['Summer16.WGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph'],                     ['WGJets_MonoPhoton_PtG-130_MC2016']],
#[['Summer16.WWTo2L2Nu_13TeV-powheg'],                                                    ['WWTo2L2Nu_MC2016']],
[['RunIISummer16MiniAODv3.WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8'],                            ['WWTo1L1Nu2Q_MC2016']],
[['RunIISummer16MiniAODv3.WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8'],                            ['WZTo1L1Nu2Q_MC2016']],
[['RunIISummer16MiniAODv3.WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8'],                              ['WZTo1L3Nu_MC2016']],
[['Summer16.ZGTo2NuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8'],                          ['ZGTo2NuG_MC2016']],
[['RunIISummer16MiniAODv3.ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8'],                              ['ZZTo2Q2Nu_MC2016']],
[['Summer16.ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8'],                               ['ZZTo2L2Q_MC2016']],
[['RunIISummer16MiniAODv3.WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8'],                                   ['WWZ_MC2016']],
[['RunIISummer16MiniAODv3.ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8'],                                   ['ZZZ_MC2016']],
[['RunIISummer16MiniAODv3.WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8'],                                   ['WZZ_MC2016']],
[['RunIISummer16MiniAODv3.TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8'],               ['TTWJetsToQQ_MC2016']],
[['RunIISummer16MiniAODv3.TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_ext2'],         ['TTWJetsToLNu_MC2016']],
[['RunIISummer16MiniAODv3.TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8'],                               ['TTZToQQ_MC2016']],
[['RunIISummer16MiniAODv3.TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_ext2'],                 ['TTZToLLNuNu_MC2016']],
#[['Summer16.TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8',
#  'Summer16.TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_ext1'],              ['TTGJets_MC2016']],
[['RunIISummer16MiniAODv3.TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8'],                                  ['TTTT_MC2016']],
]