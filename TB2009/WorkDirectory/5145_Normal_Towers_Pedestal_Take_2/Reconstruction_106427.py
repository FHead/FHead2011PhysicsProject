import FWCore.ParameterSet.Config as cms

process = cms.Process("GetPedestal")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(50000))

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring('file:/tmp/chenyi/HTB_106427.root'),
    streams   = cms.untracked.vstring('HCAL_Trigger','HCAL_SlowData','HCAL_QADCTDC','HCAL_DCC021')
)

process.hcal_db_producer = cms.ESProducer("HcalDbProducer",
   dump = cms.untracked.vstring(''),
   file = cms.untracked.string('')
)

process.es_hardcode = cms.ESSource("HcalHardcodeCalibrations",
    toGet = cms.untracked.vstring('GainWidths','PedestalWidths','QIEData','ChannelQuality','ZSThresholds','RespCorrs')
)

process.es_ascii = cms.ESSource("HcalTextCalibrations",
    input = cms.VPSet(
        cms.PSet(
            object = cms.string('ElectronicsMap'),
            file = cms.FileInPath('emap_TB2009_A.txt')
        ),
        cms.PSet(
            object = cms.string('Pedestals'),
            file = cms.FileInPath('pedestals_TB2009_106427.txt')
        ),
        cms.PSet(
            object = cms.string('Gains'),
            file = cms.FileInPath('gains_TB2009.txt')
        )
    )
)
  
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.tbUnpacker = cms.EDFilter("HcalTBObjectUnpacker",
   IncludeUnmatchedHits = cms.untracked.bool(False),
   HcalTDCFED = cms.untracked.int32(8),
   HcalQADCFED = cms.untracked.int32(8),
   HcalSlowDataFED = cms.untracked.int32(3),
   HcalTriggerFED = cms.untracked.int32(1),
   ConfigurationFile = cms.untracked.string('configQADCTDC_TB2009.txt')
)

process.hcalDigis = cms.EDFilter("HcalRawToDigi",
    UnpackZDC = cms.untracked.bool(True),
    FilterDataQuality = cms.bool(True),
    ExceptionEmptyData = cms.untracked.bool(True),
    InputLabel = cms.InputTag("source"),
    ComplainEmptyData = cms.untracked.bool(False),
    UnpackCalib = cms.untracked.bool(False),
    firstSample = cms.int32(0),
    lastSample = cms.int32(9),
    FEDs = cms.untracked.vint32(21),
    HcalFirstFED = cms.untracked.int32(21)
)
process.load("RecoLocalCalo.HcalRecProducers.HcalSimpleReconstructor_hbhe_cfi")
process.hbhereco.firstSample = 5
process.hbhereco.samplesToAdd = 4

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound', 
        'TooManyProducts', 
        'TooFewProducts')
)

process.energydistribution = cms.EDAnalyzer("FillRHEnergyDistributionAnalyzer",
    normalModule = cms.untracked.string('hbhereco'),
    output = cms.untracked.string("file:NREnergyDistribution_106427.root")
)

process.triggerfilter = cms.EDFilter("TriggerFilter",
    allowBeamTrigger = cms.untracked.bool(False),
    allowOutOfSpillPedestalTrigger = cms.untracked.bool(True),
    allowOthers = cms.untracked.bool(False)
)

process.zeroparticle = cms.EDFilter("SingleTowerParticleFilter",
    particleNumber = cms.untracked.int32(0)
)

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.p = cms.Path(
   process.tbUnpacker *
   process.hcalDigis *
   process.hbhereco *
   process.triggerfilter *
   process.zeroparticle *
   process.muonveto *
   process.energydistribution
)

