from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
#config.General.requestName = 'ttH_Analyzer_SingleElectron_Run2017B'
#config.General.requestName = 'ttH_Analyzer_SingleElectron_Run2017C'
#config.General.requestName = 'ttH_Analyzer_SingleElectron_Run2017D'
#config.General.requestName = 'ttH_Analyzer_SingleElectron_Run2017E'
#config.General.requestName = 'ttH_Analyzer_SingleElectron_Run2017F'

#config.General.requestName = 'ttH_Analyzer_SingleMuon_Run2017B'
#config.General.requestName = 'ttH_Analyzer_SingleMuon_Run2017C'
#config.General.requestName = 'ttH_Analyzer_SingleMuon_Run2017D'
#config.General.requestName = 'ttH_Analyzer_SingleMuon_Run2017E'
#config.General.requestName = 'ttH_Analyzer_SingleMuon_Run2017F'

#config.General.requestName = 'ttH_Analyzer_DoubleElectron_Run2017B'
#config.General.requestName = 'ttH_Analyzer_DoubleElectron_Run2017C'
#config.General.requestName = 'ttH_Analyzer_DoubleElectron_Run2017D'
#config.General.requestName = 'ttH_Analyzer_DoubleElectron_Run2017E'
#config.General.requestName = 'ttH_Analyzer_DoubleElectron_Run2017F'

#config.General.requestName = 'ttH_Analyzer_ElectronMuon_Run2017B'
#config.General.requestName = 'ttH_Analyzer_ElectronMuon_Run2017C'
#config.General.requestName = 'ttH_Analyzer_ElectronMuon_Run2017D'
#config.General.requestName = 'ttH_Analyzer_ElectronMuon_Run2017E'
#config.General.requestName = 'ttH_Analyzer_ElectronMuon_Run2017F'

#config.General.requestName = 'ttH_Analyzer_DoubleMuon_Run2017B'
#config.General.requestName = 'ttH_Analyzer_DoubleMuon_Run2017C'
#config.General.requestName = 'ttH_Analyzer_DoubleMuon_Run2017D'
#config.General.requestName = 'ttH_Analyzer_DoubleMuon_Run2017E'
#config.General.requestName = 'ttH_Analyzer_DoubleMuon_Run2017F'

#config.General.requestName = 'ttH_Analyzer_MET_Run2017B'
#config.General.requestName = 'ttH_Analyzer_MET_Run2017C'
#config.General.requestName = 'ttH_Analyzer_MET_Run2017D'
#config.General.requestName = 'ttH_Analyzer_MET_Run2017E'
#config.General.requestName = 'ttH_Analyzer_MET_Run2017F'

#config.General.requestName = 'ttH_Analyzer_JetHT_Run2017B'
config.General.requestName = 'ttH_Analyzer_JetHT_Run2017C'
#config.General.requestName = 'ttH_Analyzer_JetHT_Run2017D'
#config.General.requestName = 'ttH_Analyzer_JetHT_Run2017E'
#config.General.requestName = 'ttH_Analyzer_JetHT_Run2017F'

config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'test/CU_ttH_data_EDA_cfg.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.inputFiles = ['data']
config.JobType.maxJobRuntimeMin = 3600
config.JobType.maxMemoryMB = 2500

config.section_("Data")

#Single Electron
#for B-F
#config.Data.inputDataset = '/SingleElectron/Run2017B-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/SingleElectron/Run2017C-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/SingleElectron/Run2017D-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/SingleElectron/Run2017E-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/SingleElectron/Run2017F-17Nov2017-v1/MINIAOD'

#Single Muon
#for B-F
#config.Data.inputDataset = '/SingleMuon/Run2017B-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/SingleMuon/Run2017C-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/SingleMuon/Run2017D-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/SingleMuon/Run2017E-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/SingleMuon/Run2017F-17Nov2017-v1/MINIAOD'

#Double Electron
#for B-F
#config.Data.inputDataset = '/DoubleEG/Run2017B-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/DoubleEG/Run2017C-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/DoubleEG/Run2017D-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/DoubleEG/Run2017E-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/DoubleEG/Run2017F-17Nov2017-v1/MINIAOD'

#Electron Muon
#for B-F
#config.Data.inputDataset = '/MuonEG/Run2017B-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/MuonEG/Run2017C-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/MuonEG/Run2017D-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/MuonEG/Run2017E-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/MuonEG/Run2017F-17Nov2017-v1/MINIAOD'

#Double Muon
#for B-F
#config.Data.inputDataset = '/DoubleMuon/Run2017B-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/DoubleMuon/Run2017C-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/DoubleMuon/Run2017D-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/DoubleMuon/Run2017E-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/DoubleMuon/Run2017F-17Nov2017-v1/MINIAOD'

#MET
#for B-F
#config.Data.inputDataset = '/MET/Run2017B-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/MET/Run2017C-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/MET/Run2017D-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/MET/Run2017E-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/MET/Run2017F-17Nov2017-v1/MINIAOD'

#JetHT
#for B-F
#config.Data.inputDataset = '/JetHT/Run2017B-17Nov2017-v1/MINIAOD'
config.Data.inputDataset = '/JetHT/Run2017C-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017D-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017E-17Nov2017-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017F-17Nov2017-v1/MINIAOD'

config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.allowNonValidInputDataset = True
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'data/JSON/2017/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
config.Data.unitsPerJob = 20
config.Data.publication = False
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'

#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleElectron_Run2017B'
#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleElectron_Run2017C'
#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleElectron_Run2017D'
#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleElectron_Run2017E'
#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleElectron_Run2017F'

#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleMuon_Run2017B'
#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleMuon_Run2017C'
#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleMuon_Run2017D'
#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleMuon_Run2017E'
#config.Data.outputDatasetTag = 'ttH_Analyzer_SingleMuon_Run2017F'

#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleElectron_Run2017B'
#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleElectron_Run2017C'
#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleElectron_Run2017D'
#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleElectron_Run2017E'
#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleElectron_Run2017F'

#config.Data.outputDatasetTag = 'ttH_Analyzer_ElectronMuon_Run2017B'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ElectronMuon_Run2017C'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ElectronMuon_Run2017D'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ElectronMuon_Run2017E'
#config.Data.outputDatasetTag = 'ttH_Analyzer_ElectronMuon_Run2017F'

#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleMuon_Run2017B'
#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleMuon_Run2017C'
#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleMuon_Run2017D'
#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleMuon_Run2017E'
#config.Data.outputDatasetTag = 'ttH_Analyzer_DoubleMuon_Run2017F'

#config.Data.outputDatasetTag = 'ttH_Analyzer_MET_Run2017B'
#config.Data.outputDatasetTag = 'ttH_Analyzer_MET_Run2017C'
#config.Data.outputDatasetTag = 'ttH_Analyzer_MET_Run2017D'
#config.Data.outputDatasetTag = 'ttH_Analyzer_MET_Run2017E'
#config.Data.outputDatasetTag = 'ttH_Analyzer_MET_Run2017F'

#config.Data.outputDatasetTag = 'ttH_Analyzer_JetHT_Run2017B'
config.Data.outputDatasetTag = 'ttH_Analyzer_JetHT_Run2017C'
#config.Data.outputDatasetTag = 'ttH_Analyzer_JetHT_Run2017D'
#config.Data.outputDatasetTag = 'ttH_Analyzer_JetHT_Run2017E'
#config.Data.outputDatasetTag = 'ttH_Analyzer_JetHT_Run2017F'

config.Data.outLFNDirBase = '/store/user/abdatta/ttH_Analysis/Main_Analysis_2017/Data/'
config.Data.ignoreLocality = False

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
