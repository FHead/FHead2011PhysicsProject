import FWCore.ParameterSet.Config as cms

process = cms.Process("EventDisplay")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108538.root"),
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
    mip = cms.untracked.string("MIP_EarlyRejection.txt"),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False),
    usePedestalMean = cms.untracked.bool(False)
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.hitcut = cms.EDFilter("HitXFilter",
   maximum = cms.untracked.double(-5)
)

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(100)
    )
)

process.alignpion2 = cms.EDAnalyzer("AlignPulseAnalyzer",
   rejectionSample = cms.untracked.int32(2),
   rejectionHeight = cms.untracked.double(0.1),
   output = cms.untracked.string("Time_108538_2.root"),
   maxsample = cms.untracked.double(1000),
   minsample = cms.untracked.double(15)
)

process.alignpion1 = cms.EDAnalyzer("AlignPulseAnalyzer",
   rejectionSample = cms.untracked.int32(2),
   rejectionHeight = cms.untracked.double(0.1),
   output = cms.untracked.string("Time_108538_1.root"),
   maxsample = cms.untracked.double(40),
   minsample = cms.untracked.double(0)
)

process.p = cms.Path(
   process.tbunpack *
   process.ABCcut *
   process.vlsbinfo *
   process.hitcut *
   process.alignpion1 *
   process.alignpion2
)

