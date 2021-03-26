OutputBase = '/store/group/phys_heavyions/chenyi/PbPb2018/Forest/'
DatasetName = '/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v1/AODSIM'
Tag = 'PbPb2018MCRun1'

from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName = Tag

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_pponAA_MIX_103X.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.maxMemoryMB = 3500
config.JobType.maxJobRuntimeMin = 1440
#config.JobType.inputFiles = ['']

config.section_("Data")
config.Data.inputDataset = DatasetName
config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
# config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSReader/'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.publication = False
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.outputDatasetTag = Tag
config.Data.outLFNDirBase = OutputBase + DatasetName + '/'
config.Data.ignoreLocality = True
config.Data.allowNonValidInputDataset = True

config.section_("Site")
config.Site.blacklist = ['T3_US_TAMU']
config.Site.blacklist = ['T3_US_UCR']
config.Site.whitelist = ['T2_IT_Bari', 'T2_US_MIT', 'T2_CH_CERN']
config.Site.storageSite = 'T2_CH_CERN'
