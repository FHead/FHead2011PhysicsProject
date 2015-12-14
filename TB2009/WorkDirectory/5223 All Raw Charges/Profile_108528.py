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
            file = cms.FileInPath('pedestals_TB2009_108528.txt')
        ),
        cms.PSet(
            object = cms.string('Gains'),
            file = cms.FileInPath('gains_TB2009.txt')
        )
    )
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
    beamEnergy = cms.untracked.double(150),
    adcMap = cms.untracked.string('FinalAdcMapping_All.txt'),
    lowestSampleSubtraction = cms.untracked.bool(False)
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(239)
    )
)

process.vlsbreco = cms.EDProducer("HcalTBVLSBReconstructor",
    minSample = cms.untracked.uint32(0),
    maxSample = cms.untracked.uint32(31),
    adcMapFileName = cms.untracked.string('FinalAdcMapping_All.txt')
)

process.merge = cms.EDProducer("CombineCollectionProducer",
    vlsbModule = cms.untracked.string("vlsbreco"),
    normalModule = cms.untracked.string("hbhereco")
)

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.export = cms.EDAnalyzer("CExportChargeAnalyzer",
   moduleName = cms.untracked.string('merge'),
   simplified = cms.untracked.bool(False),
   exportVlsb = cms.untracked.bool(True)
)

process.runinfo = cms.EDProducer("RunInformationProducer",
   beamEnergy = cms.untracked.double(30)
)

process.hitcut = cms.EDFilter("HitXFilter",
   maximum = cms.untracked.double(-5)
)

process.timecut = cms.EDFilter("HighestSampleTimeFilter",
   minimum = cms.untracked.double(7.5),
   threshold = cms.untracked.double(100)
)


process.p = cms.Path(
    process.tbunpack *
    process.ABCcut *
    ~process.muonveto *
    process.triggerfilter *
    process.hcalDigis *
    process.hbhereco *
    process.vlsbinfo *
    process.vlsbreco *
    process.hitcut *
    process.timecut *
    process.runinfo *
    process.merge *
    process.export
)

