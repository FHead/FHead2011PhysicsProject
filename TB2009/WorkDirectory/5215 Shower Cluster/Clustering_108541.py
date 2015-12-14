import FWCore.ParameterSet.Config as cms

process = cms.Process("Clustering")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108541.root"),
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
    beamEnergy = cms.untracked.double(0),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False),
    usePedestalMean = cms.untracked.bool(False),
    adcMap = cms.untracked.string("FinalAdcMapping_All.txt")
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(100)
    )
)

process.producecluster = cms.EDProducer("ShowerClusterProducer",
    threshold = cms.untracked.double(0.2)
)

process.fillcluster = cms.EDAnalyzer("FillShowerClusterDistributions",
    ntuple = cms.untracked.bool(True),
    output = cms.untracked.string('ClusterInfo_108541.root')
)

process.averagecharge = cms.EDAnalyzer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("TotalEnergy_ABC_MinEnergy_108541.root"),
    textOutput = cms.untracked.bool(True),
    interpolate = cms.untracked.bool(False)
)

process.runinfo = cms.EDProducer("RunInformationProducer",
   beamEnergy = cms.untracked.double(0)
)

process.hitcut = cms.EDFilter("HitXFilter",
   maximum = cms.untracked.double(-5)
)

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.timecut = cms.EDFilter("HighestSampleTimeFilter",
   minimum = cms.untracked.double(7.5),
   threshold = cms.untracked.double(100)
)

process.p = cms.Path(
   process.tbunpack *
   process.ABCcut *
   process.muonveto *
   process.vlsbinfo *
   process.runinfo *
   process.hitcut *
   process.timecut *
   process.producecluster *
   process.fillcluster *
   process.averagecharge
)

