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
    baselineSamples = cms.untracked.uint32(3),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(True),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(True),
    usePedestalMean = cms.untracked.bool(True),
    pedestalMean = cms.untracked.string("PedestalMean_108525.txt"),
    mip = cms.untracked.string("MIPCalibration_Mean.txt")
)

process.averagecharge = cms.EDProducer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("mip_108525.root"),
    textOutput = cms.untracked.bool(True),
    useMIP = cms.untracked.bool(False)
)

process.percentage = cms.EDAnalyzer("FillCentralTowerEnergyPercentage",
   output = cms.untracked.string("Percentage_108525.root")
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(100)
    )
)

process.motherboard0cut = cms.EDFilter("TotalEnergyCutFilter",
    cut = cms.untracked.double(0),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False)
)

process.motherboard1cut = cms.EDFilter("TotalEnergyCutFilter",
    cut = cms.untracked.double(0),
    useMotherBoard0 = cms.untracked.bool(False),
    useMotherBoard1 = cms.untracked.bool(True),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False)
)

process.motherboard3cut = cms.EDFilter("TotalEnergyCutFilter",
    cut = cms.untracked.double(0),
    useMotherBoard0 = cms.untracked.bool(False),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(True)
)

process.motherboard0channelcut = cms.EDFilter("AllSingleLayerChargeCut",
    maximum = cms.untracked.double(200),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False)
)

process.motherboard1channelcut = cms.EDFilter("AllSingleLayerChargeCut",
    maximum = cms.untracked.double(200),
    useMotherBoard0 = cms.untracked.bool(False),
    useMotherBoard1 = cms.untracked.bool(True),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False)
)

process.motherboard3channelcut = cms.EDFilter("AllSingleLayerChargeCut",
    maximum = cms.untracked.double(200),
    useMotherBoard0 = cms.untracked.bool(False),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(True)
)

process.p = cms.Path(
    process.tbunpack *
    process.ABCcut *
    process.vlsbinfo *
    process.motherboard0cut * process.motherboard0channelcut *
    # process.motherboard1cut * process.motherboard1channelcut *
    process.motherboard3cut * process.motherboard3channelcut *
    process.averagecharge *
    process.percentage
)

