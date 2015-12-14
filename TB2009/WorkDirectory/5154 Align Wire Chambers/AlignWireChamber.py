import FWCore.ParameterSet.Config as cms

process = cms.Process("VlsbInfo")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring(
        # "file:/tmp/chenyi/HTB_106148.root",
        # "file:/tmp/chenyi/HTB_106198.root",
        "file:/tmp/chenyi/HTB_106201.root"
    ),
    streams = cms.untracked.vstring('HCAL_Trigger', 'HCAL_SlowData', 'HCAL_QADCTDC', 'HCAL_DCC021')
)

process.tbunpack = cms.EDFilter("HcalTBObjectUnpacker",
    #IncludeUnmatchedHits = cms.untracked.bool(False),
    HcalTriggerFED = cms.untracked.int32(1),
    # HcalVLSBFED = cms.untracked.int32(699),
    HcalTDCFED = cms.untracked.int32(8),
    HcalQADCFED = cms.untracked.int32(8),
    HcalSlowDataFED = cms.untracked.int32(3),
    ConfigurationFile = cms.untracked.string('configQADCTDC_TB2009.txt')
)

process.wirechamber = cms.EDAnalyzer("FillWireChamberTreeAnalyzer",
   output = cms.untracked.string("/tmp/chenyi/WireChamberTree.root")
)

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(100)
    )
)

process.p = cms.Path(process.tbunpack*process.wirechamber)
# process.p = cms.Path(process.tbunpack)

