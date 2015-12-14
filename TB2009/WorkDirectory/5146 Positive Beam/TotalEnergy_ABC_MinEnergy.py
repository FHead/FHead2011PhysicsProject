import FWCore.ParameterSet.Config as cms

process = cms.Process("VlsbInfo")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108300.root"),
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
    mip = cms.untracked.string("PercentageCorrectedNMeV.txt"),
    useMotherBoard0 = cms.untracked.bool(True),
    useMotherBoard1 = cms.untracked.bool(False),
    useMotherBoard2 = cms.untracked.bool(False),
    useMotherBoard3 = cms.untracked.bool(False),
    usePedestalMean = cms.untracked.bool(True),
    pedestalMean = cms.untracked.string("PedestalMean_108300.txt")
)

process.averagecharge = cms.EDAnalyzer("FillAverageChargeLayerAnalyzer",
    output = cms.untracked.string("TotalEnergy_ABC_MinEnergy_108300.root"),
    textOutput = cms.untracked.bool(True),
    interpolate = cms.untracked.bool(False)
)

process.ABCcut = cms.EDFilter("SingleTowerParticleFilter")

process.muonveto = cms.EDFilter("MuonVetoFilter")

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(250)
    )
)

process.clusterproducer = cms.EDProducer("ShowerClusterProducer",
    threshold = cms.untracked.double(30)
)

process.showercluster = cms.EDAnalyzer("FillShowerClusterDistributions",
    factor = cms.untracked.double(150),
    ntuple = cms.untracked.bool(True)
)

process.p = cms.Path(
   process.tbunpack *
   process.ABCcut *
   process.muonveto *
   process.vlsbinfo *
   process.averagecharge *
   process.clusterproducer *
   process.showercluster
)

