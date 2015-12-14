import FWCore.ParameterSet.Config as cms

process = cms.Process("VlsbInfo")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108525.root"),
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
    baselineSamples = cms.untracked.uint32(2),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(True),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(True),
    lowestSampleSubtraction = cms.untracked.bool(False),
    adcMap = cms.untracked.string("FinalAdcMapping_All.txt"),
    usePedestalMean = cms.untracked.bool(False)
)

process.averagecharge = cms.EDProducer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("mip_108525.root"),
    textOutput = cms.untracked.bool(True)
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.eventdisplay = cms.EDAnalyzer("FillEventDisplayAnalyzer",
   maxEvent = cms.untracked.int32(50)
)

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(100)
    )
)

process.timecut = cms.EDFilter("HighestSampleTimeFilter",
   minimum = cms.untracked.double(7.5),
   threshold = cms.untracked.double(100)
)

process.hitcut = cms.EDFilter("HitXFilter",
   maximum = cms.untracked.double(-5)
)

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.RMScut = cms.EDFilter("FirstNSampleRMSFilter",
   N = cms.untracked.int32(2),
   maximum = cms.untracked.double(1.8)
)

process.p = cms.Path(
   process.tbunpack *
   process.ABCcut *
   ~process.muonveto *
   process.vlsbinfo *
   process.hitcut *
   # process.RMScut *
   process.timecut *
   process.averagecharge *
   process.eventdisplay
)

