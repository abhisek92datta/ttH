from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
#config.General.requestName = 'ttH_Analyzer_tthbb'
#config.General.requestName = 'ttH_Analyzer_tthbb_sl'
#config.General.requestName = 'ttH_Analyzer_tthbb_dl'
#config.General.requestName = 'ttH_Analyzer_tthnonbb'
#config.General.requestName = 'ttH_Analyzer_ttjets'
#config.General.requestName = 'ttH_Analyzer_ttjets_sl'
#config.General.requestName = 'ttH_Analyzer_ttjets_sl_psweights'
#config.General.requestName = 'ttH_Analyzer_ttjets_dl'
#config.General.requestName = 'ttH_Analyzer_ttjets_dl_psweights'
config.General.requestName = 'ttH_Analyzer_ttjets_fh'
#config.General.requestName = 'ttH_Analyzer_st_s'
#config.General.requestName = 'ttH_Analyzer_st_s_psweights'
#config.General.requestName = 'ttH_Analyzer_st_t'
#config.General.requestName = 'ttH_Analyzer_st_antit'
#config.General.requestName = 'ttH_Analyzer_st_tw'
#config.General.requestName = 'ttH_Analyzer_st_tw_psweights'
#config.General.requestName = 'ttH_Analyzer_st_antitw'
#config.General.requestName = 'ttH_Analyzer_st_antitw_psweights'
#config.General.requestName = 'ttH_Analyzer_wjets_lnu'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_70_100'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_100_200'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_200_400'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_400_600'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_600_inf'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_70_100'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_100_200'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_200_400'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_400_600'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_600_800'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_800_1200'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_1200_2500'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_2500_inf'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_10_50'
#config.General.requestName = 'ttH_Analyzer_zjets_ll_mll_50_inf'
#config.General.requestName = 'ttH_Analyzer_wwjets'
#config.General.requestName = 'ttH_Analyzer_wzjets'
#config.General.requestName = 'ttH_Analyzer_zzjets'
#config.General.requestName = 'ttH_Analyzer_ttw_wlnu'
#config.General.requestName = 'ttH_Analyzer_ttw_wlnu_psweights'
#config.General.requestName = 'ttH_Analyzer_ttw_wqq'
#config.General.requestName = 'ttH_Analyzer_ttz_zllnunu'
#config.General.requestName = 'ttH_Analyzer_ttz_zllnunu_psweights'
#config.General.requestName = 'ttH_Analyzer_ttz_zqq'
#config.General.requestName = 'ttH_Analyzer_ttgjets'
#config.General.requestName = 'ttH_Analyzer_tHq'
#config.General.requestName = 'ttH_Analyzer_tHW'
#config.General.requestName = 'ttH_Analyzer_ttH_topmass_up'
#config.General.requestName = 'ttH_Analyzer_ttH_topmass_down'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'test/CU_ttH_mc_EDA_cfg.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.inputFiles = ['data']
config.JobType.maxJobRuntimeMin = 3600
config.JobType.maxMemoryMB = 2500

config.section_("Data")
#config.Data.inputDataset = '/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/ttHTobb_ttToSemiLep_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM'
#config.Data.inputDataset = '/ttHTobb_ttTo2L2Nu_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM'
#config.Data.inputDataset = '/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v2/MINIAODSIM'
#config.Data.inputDataset = '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'
#config.Data.inputDataset = '/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
config.Data.inputDataset = '/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
#config.Data.inputDataset = '/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-4to50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-4to50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-4to50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-4to50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-4to50_HT-600toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM'
#config.Data.inputDataset = '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
#config.Data.inputDataset = '/WW_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/WZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/ZZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTZToLLNuNu_M-10_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM'
#config.Data.inputDataset = '/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'
#config.Data.inputDataset = '/THQ_4f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM'
#config.Data.inputDataset = '/THW_5f_Hincl_13TeV_madgraph_pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM'
#config.Data.inputDataset = '/ttH_M125_mtop1735_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM'
#config.Data.inputDataset = '/ttH_M125_mtop1715_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM'

config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.allowNonValidInputDataset = True
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
config.Data.publication = False
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.outputDatasetTag = 'ttH_Analyzer_tthbb'
#config.Data.outputDatasetTag = 'ttH_Analyzer_tthbb_sl'
#config.Data.outputDatasetTag = 'ttH_Analyzer_tthbb_dl'
#config.Data.outputDatasetTag = 'ttH_Analyzer_tthnonbb'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttjets'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttjets_sl'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttjets_sl_psweights'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttjets_dl'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttjets_dl_psweights'
config.Data.outputDatasetTag = 'ttH_Analyzer_ttjets_fh'
#config.Data.outputDatasetTag = 'ttH_Analyzer_st_s'
#config.Data.outputDatasetTag = 'ttH_Analyzer_st_s_psweights'
#config.Data.outputDatasetTag = 'ttH_Analyzer_st_t'
#config.Data.outputDatasetTag = 'ttH_Analyzer_st_antit'
#config.Data.outputDatasetTag = 'ttH_Analyzer_st_tw'
#config.Data.outputDatasetTag = 'ttH_Analyzer_st_tw_psweights'
#config.Data.outputDatasetTag = 'ttH_Analyzer_st_antitw'
#config.Data.outputDatasetTag = 'ttH_Analyzer_st_antitw_psweights'
#config.Data.outputDatasetTag = 'ttH_Analyzer_wjets_lnu'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_70_100'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_100_200'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_200_400'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_400_600'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_4_50_ht_600_inf'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_70_100'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_100_200'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_200_400'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_400_600'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_600_800'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_800_1200'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_1200_2500'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_50_inf_ht_2500_inf'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_10_50'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zjets_ll_mll_50_inf'
#config.Data.outputDatasetTag = 'ttH_Analyzer_wwjets'
#config.Data.outputDatasetTag = 'ttH_Analyzer_wzjets'
#config.Data.outputDatasetTag = 'ttH_Analyzer_zzjets'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttw_wlnu'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttw_wlnu_psweights'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttw_wqq'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttz_zllnunu'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttz_zllnunu_psweights'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttz_zqq'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttgjets'
#config.Data.outputDatasetTag = 'ttH_Analyzer_tHq'
#config.Data.outputDatasetTag = 'ttH_Analyzer_tHW'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttH_topmass_up'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ttH_topmass_down'
config.Data.outLFNDirBase = '/store/user/abdatta/ttH_Analysis/Main_Analysis_2017/MC/'
config.Data.ignoreLocality = False

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
