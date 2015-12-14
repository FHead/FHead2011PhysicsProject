import FWCore.ParameterSet.Config as cms

process = cms.Process("ProfileCleanedMIP")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
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
            file = cms.FileInPath('pedestals_TB2009.txt')
        ),
        cms.PSet(
            object = cms.string('Gains'),
            file = cms.FileInPath('gains_TB2009.txt')
        )
    )
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

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound', 
        'TooManyProducts', 
        'TooFewProducts')
)

process.triggerfilter = cms.EDFilter("TriggerFilter",
    allowBeamTrigger = cms.untracked.bool(True),
    allowOutOfSpillPedestalTrigger = cms.untracked.bool(False),
    allowOthers = cms.untracked.bool(False)
)

process.vlsbinfo = cms.EDProducer("VLSBInformationProducer",
    minSample = cms.untracked.uint32(0),
    maxSample = cms.untracked.uint32(31),
    baselineSamples = cms.untracked.uint32(2),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False),
    usePedestalMean = cms.untracked.bool(False),
    beamEnergy = cms.untracked.double(150),
    lowestSampleSubtraction = cms.untracked.bool(False)
)

process.averagecharge = cms.EDAnalyzer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("TotalEnergy_108303.root"),
    textOutput = cms.untracked.bool(True),
    interpolate = cms.untracked.bool(False)  # interpolate for missing channels by averaging neighboring channels
)

process.averagecharge_interpolated = cms.EDAnalyzer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("TotalEnergy_Interpolated_108303.root"),
    textOutput = cms.untracked.bool(True),
    interpolate = cms.untracked.bool(True)
)

process.filladc = cms.EDAnalyzer("FillAdcDistributionAnalyzer",
    invert = cms.untracked.bool(False),
    highdef = cms.untracked.bool(True),
    divideMIP = cms.untracked.bool(False),
    baselineSubtraction = cms.untracked.bool(True),
    output = cms.untracked.string("AdcDistribution_108303.root")
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(239)
    )
)

process.energydistribution = cms.EDAnalyzer("FillCRHEnergyDistributionAnalyzer",
    module = cms.untracked.string("merge"),
    output = cms.untracked.string("EnergyDistribution_ABC_108303.root")
)

process.vlsbreco = cms.EDProducer("HcalTBVLSBReconstructor",
    minSample = cms.untracked.uint32(0),
    maxSample = cms.untracked.uint32(31)
)

process.merge = cms.EDProducer("CombineCollectionProducer",
    vlsbModule = cms.untracked.string("vlsbreco"),
    normalModule = cms.untracked.string("")
)

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.export = cms.EDAnalyzer("CExportChargeAnalyzer",
   moduleName = cms.untracked.string('merge'),
   simplified = cms.untracked.bool(False),
   exportVlsb = cms.untracked.bool(True)
)

process.runinfo = cms.EDProducer("RunInformationProducer")

process.timecut = cms.EDFilter("HighestSampleTimeFilter",
   minimum = cms.untracked.double(7.5),
   threshold = cms.untracked.double(20),
   invert = cms.untracked.bool(True)
)

process.p = cms.Path(
    process.tbunpack *
    process.ABCcut *
    ~process.muonveto *
    process.triggerfilter *
    process.vlsbinfo *
    process.runinfo *
    process.timecut *
    process.vlsbreco *
    process.merge *
    process.export
    # process.averagecharge_interpolated *
    # process.filladc
)

