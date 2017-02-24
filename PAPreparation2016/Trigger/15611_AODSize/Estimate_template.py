import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("PickEvent")

process.load("Configuration.EventContent.EventContent_cff")

process.source = cms.Source ("PoolSource",
	  fileNames = cms.untracked.vstring (
        'file:AODSIM/1AB37662-FE72-E611-B9D3-0CC47A7C3638.root',
        'file:AODSIM/5477315E-FE72-E611-9431-0CC47A7C34A6.root'),
     eventsToProcess = cms.untracked.VEventRange([__EVENTS__])
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32 (-1)
)

process.Out4 = cms.OutputModule("PoolOutputModule",
   fileName = cms.untracked.string ("/tmp/chenyi/__TAG___AOD_l4.root"),
   outputCommands = process.AODEventContent.outputCommands,
   compressionLevel = cms.untracked.int32(4)
)

process.Out7 = cms.OutputModule("PoolOutputModule",
   fileName = cms.untracked.string ("/tmp/chenyi/__TAG___AOD_l7.root"),
   outputCommands = process.AODEventContent.outputCommands,
   compressionLevel = cms.untracked.int32(7)
)

# process.MiniOut4 = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string ("/tmp/chenyi/__TAG___MiniAOD_l4.root"),
#    outputCommands = process.MINIAODEventContent.outputCommands,
#    compressionLevel = cms.untracked.int32(4)
# )
#
# process.MiniOut7 = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string ("/tmp/chenyi/__TAG___MiniAOD_l7.root"),
#    outputCommands = process.MINIAODEventContent.outputCommands,
#    compressionLevel = cms.untracked.int32(7)
# )

process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

# process.end = cms.EndPath(process.Out4 + process.Out7 + process.MiniOut4 + process.MiniOut7)
process.end = cms.EndPath(process.Out4 + process.Out7)
