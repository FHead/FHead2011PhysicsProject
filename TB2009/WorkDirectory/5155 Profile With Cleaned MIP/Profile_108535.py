import FWCore.ParameterSet.Config as cms

process = cms.Process("ProfileCleanedMIP")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108535.root"),
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
    mip = cms.untracked.string("CleanedMIP.txt"),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(True),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(True),
    usePedestalMean = cms.untracked.bool(True),
    pedestalMean = cms.untracked.string('PedestalMean_108535.txt')
)

process.averagecharge = cms.EDAnalyzer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("TotalEnergy_108535.root"),
    textOutput = cms.untracked.bool(True),
    interpolate = cms.untracked.bool(False)  # interpolate for missing channels by averaging neighboring channels
)

process.averagecharge_interpolated = cms.EDAnalyzer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("TotalEnergy_Interpolated_108535.root"),
    textOutput = cms.untracked.bool(True),
    interpolate = cms.untracked.bool(True)
)

process.filladc = cms.EDAnalyzer("FillAdcDistributionAnalyzer",
    invert = cms.untracked.bool(False),
    highdef = cms.untracked.bool(True),
    divideMIP = cms.untracked.bool(False),
    baselineSubtraction = cms.untracked.bool(True),
    output = cms.untracked.string("AdcDistribution_108535.root")
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(239)
    )
)

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.p = cms.Path(
    process.tbunpack *
    process.ABCcut *
    process.vlsbinfo *
    process.muonveto *
    process.averagecharge
    # process.averagecharge_interpolated *
    # process.filladc
)

