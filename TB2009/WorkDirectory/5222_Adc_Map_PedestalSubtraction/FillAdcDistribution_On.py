import FWCore.ParameterSet.Config as cms

process = cms.Process("VlsbInfo")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108532.root"),
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
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False),
    usePedestalMean = cms.untracked.bool(True),
    pedestalMean = cms.untracked.string('PedestalMean_108532.txt')
)

process.adc = cms.EDProducer("FillAdcDistributionAnalyzer",
    output = cms.untracked.string("Adc_On.root"),
    baselineSubtraction = cms.untracked.bool(True),
    invert = cms.untracked.bool(False),
    highdef = cms.untracked.bool(True),
    divideMIP = cms.untracked.bool(False)
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.eventdisplay = cms.EDAnalyzer("FillEventDisplayAnalyzer",
   output = cms.untracked.string("EventDisplay_108532.root"),
   maxEvent = cms.untracked.int32(100)
)

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(100)
    )
)

process.hitcut = cms.EDFilter("HitXFilter",
    maximum = cms.untracked.double(-5)
)

process.p = cms.Path(
   process.tbunpack * 
   process.ABCcut * 
   process.vlsbinfo *
   process.hitcut * 
   process.adc
   # process.eventdisplay
)

