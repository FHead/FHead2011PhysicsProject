import FWCore.ParameterSet.Config as cms

process = cms.Process("VlsbLook")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring("file:/tmp/chenyi/HTB_108541.root"),
    streams = cms.untracked.vstring('Chunk699','HCAL_Trigger'),
)

process.tbunpack = cms.EDFilter("HcalTBObjectUnpacker",
    #IncludeUnmatchedHits = cms.untracked.bool(False),
    HcalTriggerFED = cms.untracked.int32(1),
    HcalVLSBFED = cms.untracked.int32(699)
)

process.dumpAdc = cms.EDAnalyzer('DumpAdcToNtuple',
    Output = cms.untracked.string("file:/tmp/chenyi/Adc_108541.root")
)

process.MessageLogger = cms.Service("MessageLogger",
    default = cms.untracked.PSet(
        reportEvery = cms.untracked.int32(1000)
    )
)

process.p = cms.Path(process.tbunpack*process.dumpAdc)

