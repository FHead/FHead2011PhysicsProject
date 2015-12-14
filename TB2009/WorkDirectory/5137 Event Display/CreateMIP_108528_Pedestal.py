import FWCore.ParameterSet.Config as cms

process = cms.Process("VlsbInfo")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108528.root"),
    streams = cms.untracked.vstring('Chunk699', 'HCAL_Trigger', 'HCAL_SlowData', 'HCAL_QADCTDC', 'HCAL_DCC021')
)

process.tbunpack = cms.EDFilter("HcalTBObjectUnpacker",
    #IncludeUnmatchedHits = cms.untracked.bool(False),
    HcalTriggerFED = cms.untracked.int32(1),
    HcalVLSBFED = cms.untracked.int32(699),
    HcalTDCFED = cms.untracked.int32(8),
    HcalQADCFED = cms.untracked.int32(8),
    HcalSlowDataFED = cms.untracked.int32(3),
    ConfigurationFile = cms.untracked.string('configQADCTDC_TB2009.txt')
)

process.vlsbinfo = cms.EDProducer("VLSBInformationProducer",
    minSample = cms.untracked.uint32(0),
    maxSample = cms.untracked.uint32(31),
    baselineSamples = cms.untracked.uint32(3),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(True),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(True),
    usePedestalMean = cms.untracked.bool(True),
    pedestalMean = cms.untracked.string("PedestalMean_108528.txt"),
    mip = cms.untracked.string('PercentageCorrectedGeV.txt')
)

process.averagecharge = cms.EDProducer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("/tmp/chenyi/mip_108528.root"),
    textOutput = cms.untracked.bool(True),
    chargeVsEvent = cms.untracked.bool(True)
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter",
    particleNumber = cms.untracked.int32(0)
)

process.eventdisplay = cms.EDAnalyzer("FillEventDisplayAnalyzer",
   maxEvent = cms.untracked.int32(500),
   output = cms.untracked.string('/tmp/chenyi/Events_108528_Pedestal.root')
)

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(100)
    )
)

process.p = cms.Path(
   process.tbunpack * 
   process.ABCcut * 
   process.muonveto *
   process.vlsbinfo * 
   # process.averagecharge *
   process.eventdisplay
)

