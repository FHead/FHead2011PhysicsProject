import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("PickEvent")
process.source = cms.Source ("PoolSource",
      fileNames = cms.untracked.vstring (


         ),
      lumisToProcess = cms.untracked.VLuminosityBlockRange(['306126:223-306126:232'])
)

process.maxEvents = cms.untracked.PSet(
	    input = cms.untracked.int32 (-1)
)


process.Out = cms.OutputModule("PoolOutputModule",
        fileName = cms.untracked.string ('pickedEvents.root')
)

process.end = cms.EndPath(process.Out)
