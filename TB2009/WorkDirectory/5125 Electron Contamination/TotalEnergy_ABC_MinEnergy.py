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
    baselineSamples = cms.untracked.uint32(2),
    mip = cms.untracked.string("MIPCalibration"),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False)
)

process.fillfraction2 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction2_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(2),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction3 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction3_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(3),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction4 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction4_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(4),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction5 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction5_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(5),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction6 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction6_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(6),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction7 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction7_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(7),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction8 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction8_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(8),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction9 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction9_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(9),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction10 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction10_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(10),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction11 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction11_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(11),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction12 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction12_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(12),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction13 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction13_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(13),
    maxLayer = cms.untracked.int32(15)
)

process.fillfraction14 = cms.EDAnalyzer("FillLayerRangeEnergyFractionAnalyzer",
    output = cms.untracked.string("EnergyFraction14_ABC_MinEnergy_108532.root"),
    minLayer = cms.untracked.int32(14),
    maxLayer = cms.untracked.int32(15)
)

process.averagecharge = cms.EDAnalyzer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("TotalEnergy_ABC_MinEnergy_108532.root"),
    textOutput = cms.untracked.bool(True),
    interpolate = cms.untracked.bool(False)
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.maxenergycut = cms.EDFilter("TotalEnergyCutFilter",
    cut = cms.untracked.double(200)
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
   ~process.maxenergycut *
   process.fillfraction2 *
   process.fillfraction3 *
   process.fillfraction4 *
   process.fillfraction5 *
   process.fillfraction6 *
   process.fillfraction7 *
   process.fillfraction8 *
   process.fillfraction9 *
   process.fillfraction10 *
   process.fillfraction11 *
   process.fillfraction12 *
   process.fillfraction13 *
   process.fillfraction14 *
   process.averagecharge
)

