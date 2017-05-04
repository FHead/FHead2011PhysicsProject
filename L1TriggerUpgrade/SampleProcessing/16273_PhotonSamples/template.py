# Original filename: l1Stage2NtupleFromGENRAW.py

import FWCore.ParameterSet.Config as cms

from UserCode.L1TriggerUpgrade.l1Stage2NtupleFromRAW import *

from UserCode.L1TriggerUpgrade.MCSetup import *
mcSetup(process, False, True)

# job options
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

readFiles.extend( [
    '/store/group/dpg_trigger/comm_trigger/L1TrackTrigger/620_SLHC12/Extended2023TTI/Hgaga/PU__TemplatePU__/__TemplateFile__'
    ] )

# Debug stuff

#process.output = cms.OutputModule(
#    "PoolOutputModule",
#    outputCommands = cms.untracked.vstring('keep *'),
#    fileName = cms.untracked.string('output.root')
#    )

#process.e = cms.EndPath(process.output)

#process.load("L1TriggerConfig.GctConfigProducers.l1GctConfigDump_cfi")
#process.MessageLogger.cout.placeholder = cms.untracked.bool(False)
#process.MessageLogger.cout.threshold = cms.untracked.string('DEBUG')
#process.MessageLogger.debugModules = cms.untracked.vstring('l1GctConfigDump')
#process.p += ( process.l1GctConfigDump )
