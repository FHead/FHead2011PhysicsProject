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
            file = cms.FileInPath('pedestals_TB2009_108535.txt')
        ),
        cms.PSet(
            object = cms.string('Gains'),
            file = cms.FileInPath('gains_TB2009_LMIP_newpedestal.txt')
        )
    )
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
    useMotherBoard1 = cms.untracked.bool(True),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(True),
    usePedestalMean = cms.untracked.bool(False),
    mip = cms.untracked.string('MIP_EarlyRejection_Median.txt'),
    beamEnergy = cms.untracked.double(150),
    adcMap = cms.untracked.string('FinalAdcMapping_All.txt'),
    lowestSampleSubtraction = cms.untracked.bool(False)
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

process.energydistribution = cms.EDAnalyzer("FillCRHEnergyDistributionAnalyzer",
    module = cms.untracked.string("merge"),
    output = cms.untracked.string("EnergyDistribution_ABC_108535.root")
)

process.vlsbreco = cms.EDProducer("HcalTBVLSBReconstructor",
    minSample = cms.untracked.uint32(0),
    maxSample = cms.untracked.uint32(31),
    mipFileName = cms.untracked.string("MIP_EarlyRejection_Median.txt"),
    # adcMapFileName = cms.untracked.string('FinalAdcMapping_All.txt'),
    interpolate = cms.untracked.bool(True)
)

process.merge = cms.EDProducer("CombineCollectionProducer",
    vlsbModule = cms.untracked.string("vlsbreco"),
    normalModule = cms.untracked.string("hbhereco"),
    parameterizationCorrection = cms.untracked.bool(False)
)

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.timecut = cms.EDFilter("HighestSampleTimeFilter",
   minimum = cms.untracked.double(7.5),
   threshold = cms.untracked.double(100)
)

process.hitcut = cms.EDFilter("HitXFilter",
   maximum = cms.untracked.double(-7)
)

process.p = cms.Path(
    process.tbunpack *
    process.ABCcut *
    process.muonveto *
    process.triggerfilter *
    process.hcalDigis *
    process.hbhereco *
    process.vlsbinfo *
    process.vlsbreco *
    process.timecut *
    process.hitcut *
    process.merge *
    process.energydistribution
    # process.averagecharge_interpolated *
    # process.filladc
)

