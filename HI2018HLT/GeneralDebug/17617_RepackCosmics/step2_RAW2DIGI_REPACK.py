# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: step2 --step RAW2DIGI,REPACK:DigiToHybridRawRepack -n 100 --conditions auto:run2_data --processName EMULATEHYBRID --scenario HeavyIons --datatier RAW --customise RecoLocalTracker/SiStripZeroSuppression/customiseHybrid.addHybridEmulationBeforeRepack --data --era Run2_HI --eventcontent RAW --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('EMULATEHYBRID',eras.Run2_HI)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.DigiToRaw_Repack_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    # fileNames = cms.untracked.vstring('/store/data/Run2018D/Cosmics/RAW/v1/000/322/670/00000/7C2FA229-93B5-E811-A40B-FA163E8092C9.root'),
    # fileNames = cms.untracked.vstring('/store/data/Run2018D/HLTPhysics/RAW/v1/000/322/633/00000/EAE34FB6-13B5-E811-B132-FA163E75201A.root'),
    fileNames = cms.untracked.vstring('/store/data/Run2018D/JetHT/RAW/v1/000/322/633/00000/185EB3AC-EEB4-E811-BD6E-FA163E57B0C7.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RAWoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RAW'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('/tmp/chenyi/step2_RAW2DIGI_REPACK.root'),
    outputCommands = process.RAWEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.digi2repack_step = cms.Path(process.DigiToHybridRawRepack)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWoutput_step = cms.EndPath(process.RAWoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.digi2repack_step,process.endjob_step,process.RAWoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# customisation of the process.

# Automatic addition of the customisation function from RecoLocalTracker.SiStripZeroSuppression.customiseHybrid
from RecoLocalTracker.SiStripZeroSuppression.customiseHybrid import addHybridEmulationBeforeRepack

#call to customisation function addHybridEmulationBeforeRepack imported from RecoLocalTracker.SiStripZeroSuppression.customiseHybrid
process = addHybridEmulationBeforeRepack(process)

# End of customisation functions

# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
