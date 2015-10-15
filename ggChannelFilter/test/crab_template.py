from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'NAME'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'makeTuples_cfg.py'

config.Data.inputDataset = 'DATASET'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 64
config.Data.outLFNDirBase = '/store/user/%s/ggChannel_tuples_v2' % (getUsernameFromSiteDB())

config.Site.storageSite = "T3_TW_NTU_HEP"
