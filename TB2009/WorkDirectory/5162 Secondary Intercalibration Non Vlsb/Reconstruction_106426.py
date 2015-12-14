import FWCore.ParameterSet.Config as cms

process = cms.Process("PrintCharges")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(50000))

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring('file:/tmp/chenyi/HTB_106426.root'),
    streams   = cms.untracked.vstring('HCAL_Trigger','HCAL_SlowData','HCAL_QADCTDC','HCAL_DCC021','Chunk699')
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
            file = cms.FileInPath('pedestals_TB2009_106426.txt')
        ),
        cms.PSet(
            object = cms.string('Gains'),
            file = cms.FileInPath('gains_TB2009_PercentageCorrectedGeV.txt')
        )
    )
)
  
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.tbUnpacker = cms.EDFilter("HcalTBObjectUnpacker",
   IncludeUnmatchedHits = cms.untracked.bool(False),
   HcalTDCFED = cms.untracked.int32(8),
   HcalQADCFED = cms.untracked.int32(8),
   HcalSlowDataFED = cms.untracked.int32(3),
   HcalTriggerFED = cms.untracked.int32(1),
   # HcalVLSBFED = cms.untracked.int32(699),
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

process.oneparticle = cms.EDFilter("SingleTowerParticleFilter",
    particleNumber = cms.untracked.int32(1)
)

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.export = cms.EDAnalyzer("ExportChargeAnalyzer",
   normalModule = cms.untracked.string('hbhereco'),
   exportVlsb = cms.untracked.bool(False),
   simplified = cms.untracked.bool(False),
   sidetowersimplified = cms.untracked.bool(True)
)

process.vlsbinfo = cms.EDProducer("VLSBInformationProducer",
    minSample = cms.untracked.uint32(0),
    maxSample = cms.untracked.uint32(31),
    baselineSamples = cms.untracked.uint32(2),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(True),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(True),
    usePedestalMean = cms.untracked.bool(True),
    pedestalMean = cms.untracked.string("PedestalMean_106426.txt"),
    mip = cms.untracked.string('SecondaryMIP.txt'),
    roughmip = cms.untracked.string('PercentageCorrectedGeV.txt'),
    beamEnergy = cms.untracked.double(150),
    adcMap = cms.untracked.string('FinalAdcMapping_All.txt'),
    lowestSampleSubtraction = cms.untracked.bool(True),
    numberOfSamplesForSubtraction = cms.untracked.int32(16),
    numberOfSamplesToSkip = cms.untracked.int32(16)
)

process.vlsbreco = cms.EDProducer("HcalTBVLSBReconstructor",
    minSample = cms.untracked.uint32(0),
    maxSample = cms.untracked.uint32(31),
    mipFileName = cms.untracked.string("PercentageCorrectedGeV.txt"),
    pedestalMeanFileName = cms.untracked.string("PedestalMean_106426.txt"),
    adcMapFileName = cms.untracked.string("FinalAdcMapping_All.txt")
)

process.energydistribution = cms.EDAnalyzer("FillRHEnergyDistributionAnalyzer",
    vlsbModule = cms.untracked.string(""),
    normalModule = cms.untracked.string("hbhereco"),
    output = cms.untracked.string("EnergyDistribution_ABC_106426.root")
)

process.maxenergycut = cms.EDFilter("RHTotalEnergyCut",
    minimum = cms.untracked.double(5)
)

process.p = cms.Path(
   process.tbUnpacker *
   # process.vlsbinfo *
   # process.vlsbreco *
   process.hcalDigis *
   process.hbhereco *
   process.triggerfilter *
   process.oneparticle *
   ~process.muonveto *
   ~process.maxenergycut *
   process.export
)

