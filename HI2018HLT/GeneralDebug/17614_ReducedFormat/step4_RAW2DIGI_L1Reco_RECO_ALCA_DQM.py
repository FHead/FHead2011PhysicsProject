# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: step4 --conditions auto:run2_data -s RAW2DIGI,L1Reco,RECO,ALCA:SiStripCalZeroBias+SiStripCalMinBias+TkAlMinBiasHI+TkAlUpsilonMuMuHI+TkAlZMuMuHI+TkAlMuonIsolatedHI+TkAlJpsiMuMuHI+HcalCalMinBias,DQM --process reRECO -n -1 --data --era Run2_HI --eventcontent RECO,DQM --runUnscheduled --scenario HeavyIons --datatier RECO,DQMIO --repacked --no_exec --filein file:outputStreamMuonFullRAW.root
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('reRECO',eras.Run2_HI)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.AlCaRecoStreamsHeavyIons_cff')
process.load('DQMOffline.Configuration.DQMOfflineHeavyIons_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
      fileNames = cms.untracked.vstring('file:outputStreamMuonFullRAW.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step4 nevts:-1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('step4_RAW2DIGI_L1Reco_RECO_ALCA_DQM.root'),
    outputCommands = process.RECOEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

process.DQMoutput = cms.OutputModule("DQMRootOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('DQMIO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('step4_RAW2DIGI_L1Reco_RECO_ALCA_DQM_inDQM.root'),
    outputCommands = process.DQMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition
process.ALCARECOStreamHcalCalMinBias = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOHcalCalMinBias')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALCARECO'),
        filterName = cms.untracked.string('HcalCalMinBias')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('HcalCalMinBias.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_hltTriggerSummaryAOD_*_*',
        'keep *_TriggerResults_*_*',
        'keep HcalNoiseSummary_hcalnoise_*_*',
        'keep HBHERecHitsSorted_hbhereco_*_*',
        'keep HORecHitsSorted_horeco_*_*',
        'keep HFRecHitsSorted_hfreco_*_*',
        'keep HFRecHitsSorted_hfrecoMBNZS_*_*',
        'keep HBHERecHitsSorted_hbherecoNoise_*_*',
        'keep HORecHitsSorted_horecoNoise_*_*',
        'keep HFRecHitsSorted_hfrecoNoise_*_*'
    )
)
process.ALCARECOStreamSiStripCalMinBias = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOSiStripCalMinBias')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALCARECO'),
        filterName = cms.untracked.string('SiStripCalMinBias')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('SiStripCalMinBias.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_ALCARECOSiStripCalMinBias_*_*',
        'keep *_siStripClusters_*_*',
        'keep *_siPixelClusters_*_*',
        'keep DetIdedmEDCollection_siStripDigis_*_*',
        'keep L1AcceptBunchCrossings_*_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
        'keep LumiScalerss_scalersRawToDigi_*_*',
        'keep DcsStatuss_scalersRawToDigi_*_*',
        'keep *_TriggerResults_*_*'
    )
)
process.ALCARECOStreamSiStripCalZeroBias = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOSiStripCalZeroBias')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALCARECO'),
        filterName = cms.untracked.string('SiStripCalZeroBias')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('SiStripCalZeroBias.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_ALCARECOSiStripCalZeroBias_*_*',
        'keep *_calZeroBiasClusters_*_*',
        'keep L1AcceptBunchCrossings_*_*_*',
        'keep *_TriggerResults_*_*'
    )
)
process.ALCARECOStreamTkAlJpsiMuMuHI = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOTkAlJpsiMuMuHI')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALCARECO'),
        filterName = cms.untracked.string('TkAlJpsiMuMuHI')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('TkAlJpsiMuMuHI.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_ALCARECOTkAlJpsiMuMuHI_*_*',
        'keep L1AcceptBunchCrossings_*_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
        'keep *_TriggerResults_*_*',
        'keep DcsStatuss_scalersRawToDigi_*_*',
        'keep *_hiSelectedVertex_*_*'
    )
)
process.ALCARECOStreamTkAlMinBiasHI = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOTkAlMinBiasHI')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALCARECO'),
        filterName = cms.untracked.string('TkAlMinBiasHI')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('TkAlMinBiasHI.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_ALCARECOTkAlMinBiasHI_*_*',
        'keep L1AcceptBunchCrossings_*_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
        'keep *_TriggerResults_*_*',
        'keep DcsStatuss_scalersRawToDigi_*_*',
        'keep *_hiSelectedVertex_*_*',
        'keep *_offlineBeamSpot_*_*'
    )
)
process.ALCARECOStreamTkAlMuonIsolatedHI = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOTkAlMuonIsolatedHI')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALCARECO'),
        filterName = cms.untracked.string('TkAlMuonIsolatedHI')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('TkAlMuonIsolatedHI.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_ALCARECOTkAlMuonIsolatedHI_*_*',
        'keep L1AcceptBunchCrossings_*_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
        'keep *_TriggerResults_*_*',
        'keep DcsStatuss_scalersRawToDigi_*_*',
        'keep *_hiSelectedVertex_*_*'
    )
)
process.ALCARECOStreamTkAlUpsilonMuMuHI = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOTkAlUpsilonMuMuHI')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALCARECO'),
        filterName = cms.untracked.string('TkAlUpsilonMuMuHI')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('TkAlUpsilonMuMuHI.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_ALCARECOTkAlUpsilonMuMuHI_*_*',
        'keep L1AcceptBunchCrossings_*_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
        'keep *_TriggerResults_*_*',
        'keep DcsStatuss_scalersRawToDigi_*_*',
        'keep *_hiSelectedVertex_*_*'
    )
)
process.ALCARECOStreamTkAlZMuMuHI = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOTkAlZMuMuHI')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALCARECO'),
        filterName = cms.untracked.string('TkAlZMuMuHI')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('TkAlZMuMuHI.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_ALCARECOTkAlZMuMuHI_*_*',
        'keep L1AcceptBunchCrossings_*_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
        'keep *_TriggerResults_*_*',
        'keep DcsStatuss_scalersRawToDigi_*_*',
        'keep *_hiSelectedVertex_*_*'
    )
)

# Other statements
process.ALCARECOEventContent.outputCommands.extend(process.OutALCARECOTkAlMuonIsolatedHI_noDrop.outputCommands)
process.ALCARECOEventContent.outputCommands.extend(process.OutALCARECOTkAlUpsilonMuMuHI_noDrop.outputCommands)
process.ALCARECOEventContent.outputCommands.extend(process.OutALCARECOTkAlJpsiMuMuHI_noDrop.outputCommands)
process.ALCARECOEventContent.outputCommands.extend(process.OutALCARECOSiStripCalZeroBias_noDrop.outputCommands)
process.ALCARECOEventContent.outputCommands.extend(process.OutALCARECOTkAlZMuMuHI_noDrop.outputCommands)
process.ALCARECOEventContent.outputCommands.extend(process.OutALCARECOSiStripCalMinBias_noDrop.outputCommands)
process.ALCARECOEventContent.outputCommands.extend(process.OutALCARECOHcalCalMinBias_noDrop.outputCommands)
process.ALCARECOEventContent.outputCommands.extend(process.OutALCARECOTkAlMinBiasHI_noDrop.outputCommands)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
process.dqmoffline_step = cms.EndPath(process.DQMOfflineHeavyIons)
process.dqmofflineOnPAT_step = cms.EndPath(process.DQMOfflineHeavyIons)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)
process.DQMoutput_step = cms.EndPath(process.DQMoutput)
process.ALCARECOStreamHcalCalMinBiasOutPath = cms.EndPath(process.ALCARECOStreamHcalCalMinBias)
process.ALCARECOStreamSiStripCalMinBiasOutPath = cms.EndPath(process.ALCARECOStreamSiStripCalMinBias)
process.ALCARECOStreamSiStripCalZeroBiasOutPath = cms.EndPath(process.ALCARECOStreamSiStripCalZeroBias)
process.ALCARECOStreamTkAlJpsiMuMuHIOutPath = cms.EndPath(process.ALCARECOStreamTkAlJpsiMuMuHI)
process.ALCARECOStreamTkAlMinBiasHIOutPath = cms.EndPath(process.ALCARECOStreamTkAlMinBiasHI)
process.ALCARECOStreamTkAlMuonIsolatedHIOutPath = cms.EndPath(process.ALCARECOStreamTkAlMuonIsolatedHI)
process.ALCARECOStreamTkAlUpsilonMuMuHIOutPath = cms.EndPath(process.ALCARECOStreamTkAlUpsilonMuMuHI)
process.ALCARECOStreamTkAlZMuMuHIOutPath = cms.EndPath(process.ALCARECOStreamTkAlZMuMuHI)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.pathALCARECOTkAlMuonIsolatedHI,process.pathALCARECOTkAlUpsilonMuMuHI,process.pathALCARECOTkAlJpsiMuMuHI,process.pathALCARECOSiStripCalZeroBias,process.pathALCARECOTkAlZMuMuHI,process.pathALCARECOSiStripCalMinBias,process.pathALCARECOHcalCalMinBias,process.pathALCARECOTkAlMinBiasHI,process.dqmoffline_step,process.dqmofflineOnPAT_step,process.RECOoutput_step,process.DQMoutput_step,process.ALCARECOStreamHcalCalMinBiasOutPath,process.ALCARECOStreamSiStripCalMinBiasOutPath,process.ALCARECOStreamSiStripCalZeroBiasOutPath,process.ALCARECOStreamTkAlJpsiMuMuHIOutPath,process.ALCARECOStreamTkAlMinBiasHIOutPath,process.ALCARECOStreamTkAlMuonIsolatedHIOutPath,process.ALCARECOStreamTkAlUpsilonMuMuHIOutPath,process.ALCARECOStreamTkAlZMuMuHIOutPath)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

from Configuration.Applications.ConfigBuilder import MassReplaceInputTag
MassReplaceInputTag(process)

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
