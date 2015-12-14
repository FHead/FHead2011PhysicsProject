import FWCore.ParameterSet.Config as cms

process = cms.Process("VlsbInfo")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108303.root"),
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
    mip = cms.untracked.string("MIPCalibration_preampoff.txt"),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False)
)

process.fillfraction = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    minLayer = cms.untracked.int32(8),
    maxLayer = cms.untracked.int32(15),
    output = cms.untracked.string("MuonFraction_Contamination.root"),
)

process.maxenergy = cms.EDFilter("TotalEnergyCutFilter",
    cut = cms.untracked.double(300)
)

process.averagecharge = cms.EDAnalyzer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("TotalEnergy_Muon_Contamination_108303.root"),
    textOutput = cms.untracked.bool(True),
    interpolate = cms.untracked.bool(False)
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.eventdisplay = cms.EDAnalyzer("FillEventDisplayAnalyzer",
    output = cms.untracked.string("MuonEvents_Contamination_108303.root")
)

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(250)
    )
)

process.p = cms.Path(
   process.tbunpack *
   process.ABCcut *
   process.vlsbinfo *
   ~process.maxenergy *
   process.fillfraction *
   process.averagecharge *
   process.eventdisplay
)

