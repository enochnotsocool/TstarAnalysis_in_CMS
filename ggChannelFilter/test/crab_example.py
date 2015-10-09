from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'TstarToTgluon_Pt25'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'makeTuples_cfg.py'
config.JobType.pyCfgParams = ['jetLimit=25']

config.Data.inputDataset = '/TstarTstarToTgluonTgluon_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 64
config.Data.outLFNDirBase = '/store/user/%s/ggChannel_jetPT_test' % (getUsernameFromSiteDB())

config.Site.storageSite = "T3_TW_NTU_HEP"
