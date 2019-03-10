OutputBase = '/store/group/phys_heavyions/chenyi/MCTruth/102X/'
# DatasetName = '/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/RunIIFall17DRStdmix-NoPU_94X_mc2017_realistic_v10-v2/AODSIM'
# Tag = 'MCTruth2017NoPU'

from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName = Tag

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'run_JRA_cfg.py'
config.JobType.allowUndistributedCMSSW = True
#config.JobType.inputFiles = ['']

config.section_("Data")
config.Data.inputDataset = DatasetName
config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.publication = False
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.outputDatasetTag = Tag
config.Data.outLFNDirBase = OutputBase + DatasetName + '/'
config.Data.ignoreLocality = True

config.section_("Site")
config.Site.blacklist = ['T3_US_TAMU']
config.Site.blacklist = ['T3_US_UCR']
config.Site.whitelist = ['T2_IT_Bari']
config.Site.storageSite = 'T2_CH_CERN'
