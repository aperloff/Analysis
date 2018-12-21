#format for dict entries:
#                            MC: [['sample'] , ['short name']]
#                  MC w/ mother: [['sample'] , ['short name',mother PDGID(s)]]
#         MC w/ extended sample: [['sample','sample_ext'] , ['short name']]
#MC w/ extended sample & mother: [['sample','sample_ext'] , ['short name',mother PDGID(s)]]

flist = [
[['RunIIFall17MiniAODv2.QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8'],                ['QCD_HT-200to300_MC2017']],
[['RunIIFall17MiniAODv2.QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8'],                ['QCD_HT-300to500_MC2017']],
[['RunIIFall17MiniAODv2.QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8'],                ['QCD_HT-500to700_MC2017']],
[['RunIIFall17MiniAODv2.QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8'],               ['QCD_HT-700to1000_MC2017']],
[['RunIIFall17MiniAODv2.QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8'],              ['QCD_HT-1000to1500_MC2017']],
[['RunIIFall17MiniAODv2.QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8'],              ['QCD_HT-1500to2000_MC2017']],
[['RunIIFall17MiniAODv2.QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8'],               ['QCD_HT-2000toInf_MC2017']],
[['RunIIFall17MiniAODv2.WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8'],        ['WJetsToLNu_HT-100to200_MC2017']],
[['RunIIFall17MiniAODv2.WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8'],        ['WJetsToLNu_HT-200to400_MC2017']],
[['RunIIFall17MiniAODv2.WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8'],        ['WJetsToLNu_HT-400to600_MC2017']],
[['RunIIFall17MiniAODv2.WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8'],        ['WJetsToLNu_HT-600to800_MC2017']],
[['RunIIFall17MiniAODv2.WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8'],       ['WJetsToLNu_HT-800to1200_MC2017']],
[['RunIIFall17MiniAODv2.WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8'],      ['WJetsToLNu_HT-1200to2500_MC2017']],
[['RunIIFall17MiniAODv2.WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8'],       ['WJetsToLNu_HT-2500toInf_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_TuneCP5_13TeV-madgraphMLM-pythia8'],                             ['TTJets_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8'],        ['TTJets_SingleLeptFromT_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8'],     ['TTJets_SingleLeptFromTbar_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8'],                 ['TTJets_DiLept_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_SingleLeptFromT_genMET-150_TuneCP5_13TeV-madgraphMLM-pythia8'],  ['TTJets_SingleLeptFromT_genMET-150_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_SingleLeptFromTbar_genMET-150_TuneCP5_13TeV-madgraphMLM-pythia8'],  ['TTJets_SingleLeptFromTbar_genMET-150_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_DiLept_genMET-150_TuneCP5_13TeV-madgraphMLM-pythia8'],           ['TTJets_DiLept_genMET-150_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8'],            ['TTJets_HT-600to800_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8'],           ['TTJets_HT-800to1200_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8'],          ['TTJets_HT-1200to2500_MC2017']],
[['RunIIFall17MiniAODv2.TTJets_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8'],           ['TTJets_HT-2500toInf_MC2017']],
[['RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8',
  'RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8_ext1'],   ['DYJetsToLL_M-50_HT-100to200_MC2017']],
[['RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8',
  'RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8_ext1'],   ['DYJetsToLL_M-50_HT-200to400_MC2017']],
[['RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8',
  'RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8_ext1'],   ['DYJetsToLL_M-50_HT-400to600_MC2017']],
[['RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8'],        ['DYJetsToLL_M-50_HT-600to800_MC2017']],
[['RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8'],       ['DYJetsToLL_M-50_HT-800to1200_MC2017']],
[['RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8'],      ['DYJetsToLL_M-50_HT-1200to2500_MC2017']],
[['RunIIFall17MiniAODv2.DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8'],       ['DYJetsToLL_M-50_HT-2500toInf_MC2017']],
[['RunIIFall17MiniAODv2.DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8',
  'RunIIFall17MiniAODv2.DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_ext1'],               ['DYJetsToLL_M-50_MC2017']],
[['RunIIFall17MiniAODv2.ZJetsToNuNu_HT-100To200_13TeV-madgraph'],                               ['ZJetsToNuNu_HT-100to200_MC2017']],
[['RunIIFall17MiniAODv2.ZJetsToNuNu_HT-200To400_13TeV-madgraph'],                               ['ZJetsToNuNu_HT-200to400_MC2017']],
[['RunIIFall17MiniAODv2.ZJetsToNuNu_HT-400To600_13TeV-madgraph'],                               ['ZJetsToNuNu_HT-400to600_MC2017']],
[['RunIIFall17MiniAODv2.ZJetsToNuNu_HT-600To800_13TeV-madgraph'],                                    ['ZJetsToNuNu_HT-600to800_MC2017']],
[['RunIIFall17MiniAODv2.ZJetsToNuNu_HT-800To1200_13TeV-madgraph'],                                   ['ZJetsToNuNu_HT-800to1200_MC2017']],
[['RunIIFall17MiniAODv2.ZJetsToNuNu_HT-1200To2500_13TeV-madgraph'],                             ['ZJetsToNuNu_HT-1200to2500_MC2017']],
[['RunIIFall17MiniAODv2.ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph'],                                   ['ZJetsToNuNu_HT-2500toInf_MC2017']],
[['RunIIFall17MiniAODv2.GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8'],             ['GJets_HT-100to200_MC2017']],
[['RunIIFall17MiniAODv2.GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8'],             ['GJets_HT-200to400_MC2017']],
[['RunIIFall17MiniAODv2.GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8'],             ['GJets_HT-400to600_MC2017']],
[['RunIIFall17MiniAODv2.GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8'],             ['GJets_HT-600toInf_MC2017']],
#[['RunIIFall17MiniAODv2.GJets_DR-0p4_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8'],           ['GJets_DR-0p4_HT-100to200_MC2017']],
#[['RunIIFall17MiniAODv2.GJets_DR-0p4_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8'],           ['GJets_DR-0p4_HT-200to400_MC2017']],
#[['RunIIFall17MiniAODv2.GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8'],           ['GJets_DR-0p4_HT-400to600_MC2017']],
#[['RunIIFall17MiniAODv2.GJets_DR-0p4_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8'],           ['GJets_DR-0p4_HT-600toInf_MC2017']],
[['RunIIFall17MiniAODv2.ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8'],          ['ST_s-channel_MC2017']],
[['RunIIFall17MiniAODv2.ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8'],        ['ST_t-channel_top_MC2017']],
[['RunIIFall17MiniAODv2.ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8'],    ['ST_t-channel_antitop_MC2017']],
[['RunIIFall17MiniAODv2.ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_PSweights_13TeV-powheg-pythia8'],         ['ST_tW_top_MC2017']],
[['RunIIFall17MiniAODv2.ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_PSweights_13TeV-powheg-pythia8'],     ['ST_tW_antitop_MC2017']],
[['RunIIFall17MiniAODv2.WGJets_MonoPhoton_PtG-40to130_TuneCP5_13TeV-madgraph'],                 ['WGJets_MonoPhoton_PtG-40to130_MC2017']],
#[['RunIIFall17MiniAODv2.WGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph'],                     ['WGJets_MonoPhoton_PtG-130_MC2017']],
#[['RunIIFall17MiniAODv2.WWTo2L2Nu_13TeV-powheg'],                                                    ['WWTo2L2Nu_MC2017']],
[['RunIIFall17MiniAODv2.WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8'],                            ['WWTo1L1Nu2Q_MC2017']],
[['RunIIFall17MiniAODv2.WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8'],                            ['WZTo1L1Nu2Q_MC2017']],
[['RunIIFall17MiniAODv2.WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2'],                              ['WZTo1L3Nu_MC2017']],
#[['RunIIFall17MiniAODv2.ZGTo2NuG_TuneCP5_13TeV-amcatnloFXFX-pythia8'],                          ['ZGTo2NuG_MC2017']],
#[['RunIIFall17MiniAODv2.ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8'],                              ['ZZTo2Q2Nu_MC2017']],
[['RunIIFall17MiniAODv2.ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8'],                               ['ZZTo2L2Q_MC2017']],
#[['RunIIFall17MiniAODv2.WWZ_TuneCP5_13TeV-amcatnlo-pythia8'],                                   ['WWZ_MC2017']],
[['RunIIFall17MiniAODv2.ZZZ_TuneCP5_13TeV-amcatnlo-pythia8'],                                   ['ZZZ_MC2017']],
[['RunIIFall17MiniAODv2.WZZ_TuneCP5_13TeV-amcatnlo-pythia8'],                                   ['WZZ_MC2017']],
[['RunIIFall17MiniAODv2.TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8'],               ['TTWJetsToQQ_MC2017']],
[['RunIIFall17MiniAODv2.TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8',
  'RunIIFall17MiniAODv2.TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8'],         ['TTWJetsToLNu_MC2017']],
[['RunIIFall17MiniAODv2.TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8'],                               ['TTZToQQ_MC2017']],
[['RunIIFall17MiniAODv2.TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8'],                 ['TTZToLLNuNu_MC2017']],
[['RunIIFall17MiniAODv2.TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8',
  'RunIIFall17MiniAODv2.TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_ext1'],              ['TTGJets_MC2017']],
[['RunIIFall17MiniAODv2.TTGamma_SingleLeptFromT_TuneCP5_PSweights_13TeV_madgraph_pythia8'],      ['TTGamma_SingleLeptFromT_MC2017']],
[['RunIIFall17MiniAODv2.TTGamma_SingleLeptFromTbar_TuneCP5_PSweights_13TeV_madgraph_pythia8'],      ['TTGamma_SingleLeptFromTbar_MC2017']],
[['RunIIFall17MiniAODv2.TTGamma_Dilept_TuneCP5_PSweights_13TeV_madgraph_pythia8'],      ['TTGamma_Dilept_MC2017']],
[['RunIIFall17MiniAODv2.TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8'],                                  ['TTTT_MC2017']],
]