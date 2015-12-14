import FWCore.ParameterSet.Config as cms

process = cms.Process("WireChamberStudy")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108538.root"),
    streams = cms.untracked.vstring('HCAL_Trigger', 'HCAL_SlowData', 'HCAL_QADCTDC', 'HCAL_DCC021', 'Chunk699')
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
    pedestalMean = cms.untracked.string("PedestalMean_108538.txt"),
    mip = cms.untracked.string('PercentageCorrectedGeV.txt'),
    beamEnergy = cms.untracked.double(30),
    adcMap = cms.untracked.string('FinalAdcMapping_All.txt'),
    interCalibration = cms.untracked.string("InterCalibration.txt")
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

process.wirechamber = cms.EDAnalyzer("FillExtrapolatedHitPointAnalyzer",
   output = cms.untracked.string("ExtrapolatedHit.root")
)

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(100)
    )
)

process.p = cms.Path(process.tbunpack*process.vlsbinfo*process.wirechamber)
# process.p = cms.Path(process.tbunpack)

