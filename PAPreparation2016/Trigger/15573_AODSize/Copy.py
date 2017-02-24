import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("PickEvent")

process.load("Configuration.EventContent.EventContent_cff")

process.source = cms.Source ("PoolSource",
	  fileNames = cms.untracked.vstring (
        'file:Done/Copy_1.root',
        'file:Done/Copy_2.root',
        'file:Done/Copy_3.root',
        'file:Done/Copy_4.root',
        'file:Done/Copy_5.root',
        'file:Done/Copy_6.root',
        'file:Done/Copy_7.root',
        'file:Done/Copy_8.root',
        'file:Done/Copy_9.root',
        'file:Done/Copy_10.root',
        'file:Done/Copy_11.root',
        'file:Done/Copy_12.root',
        'file:Done/Copy_13.root',
        'file:Done/Copy_14.root',
        'file:Done/Copy_15.root',
        'file:Done/Copy_16.root',
        'file:Done/Copy_17.root',
        'file:Done/Copy_18.root',
        'file:Done/Copy_19.root',
        'file:Done/Copy_20.root',
        'file:Done/Copy_21.root',
        'file:Done/Copy_22.root',
        'file:Done/Copy_23.root',
        'file:Done/Copy_24.root',
        'file:Done/Copy_25.root',
        'file:Done/Copy_26.root',
        'file:Done/Copy_27.root',
        'file:Done/Copy_28.root',
        'file:Done/Copy_29.root',
        'file:Done/Copy_30.root',
        'file:Done/Copy_31.root',
        'file:Done/Copy_32.root',
        'file:Done/Copy_33.root',
        'file:Done/Copy_34.root',
        'file:Done/Copy_35.root',
        'file:Done/Copy_36.root',
        'file:Done/Copy_37.root',
        'file:Done/Copy_38.root',
        'file:Done/Copy_39.root',
        'file:Done/Copy_40.root',
        'file:Done/Copy_41.root',
        'file:Done/Copy_42.root',
        'file:Done/Copy_43.root',
        'file:Done/Copy_44.root',
        'file:Done/Copy_45.root',
        'file:Done/Copy_46.root',
        'file:Done/Copy_47.root',
        'file:Done/Copy_48.root',
        'file:Done/Copy_49.root',
        'file:Done/Copy_50.root',
        'file:Done/Copy_51.root',
        'file:Done/Copy_52.root',
        'file:Done/Copy_53.root',
        'file:Done/Copy_54.root',
        'file:Done/Copy_55.root',
        'file:Done/Copy_56.root',
        'file:Done/Copy_57.root',
        'file:Done/Copy_58.root',
        'file:Done/Copy_59.root',
        'file:Done/Copy_60.root',
        'file:Done/Copy_61.root',
        'file:Done/Copy_62.root',
        'file:Done/Copy_63.root',
        'file:Done/Copy_64.root',
        'file:Done/Copy_65.root',
        'file:Done/Copy_66.root',
        'file:Done/Copy_67.root',
        'file:Done/Copy_68.root',
        'file:Done/Copy_69.root',
        'file:Done/Copy_70.root',
        'file:Done/Copy_71.root',
        'file:Done/Copy_72.root',
        'file:Done/Copy_73.root',
        'file:Done/Copy_74.root',
        'file:Done/Copy_75.root',
        'file:Done/Copy_76.root',
        'file:Done/Copy_77.root',
        'file:Done/Copy_78.root',
        'file:Done/Copy_79.root',
        'file:Done/Copy_80.root',
        'file:Done/Copy_81.root',
        'file:Done/Copy_82.root',
        'file:Done/Copy_83.root',
        'file:Done/Copy_84.root',
        'file:Done/Copy_85.root',
        'file:Done/Copy_86.root',
        'file:Done/Copy_87.root',
        'file:Done/Copy_88.root',
        'file:Done/Copy_89.root',
        'file:Done/Copy_90.root',
        'file:Done/Copy_91.root',
        'file:Done/Copy_92.root',
        'file:Done/Copy_93.root',
        'file:Done/Copy_94.root',
        'file:Done/Copy_95.root',
        'file:Done/Copy_96.root',
        'file:Done/Copy_97.root',
        'file:Done/Copy_98.root',
        'file:Done/Copy_99.root',
        'file:Done/Copy_100.root'),
)

process.maxEvents = cms.untracked.PSet(
	    input = cms.untracked.int32 (-1)
)


process.Out4 = cms.OutputModule("PoolOutputModule",
   fileName = cms.untracked.string ("MergedWithItself_AOD_l4.root"),
   outputCommands = process.AODEventContent.outputCommands,
   compressionLevel = cms.untracked.int32(4)
)

process.Out7 = cms.OutputModule("PoolOutputModule",
   fileName = cms.untracked.string ("MergedWithItself_AOD_l7.root"),
   outputCommands = process.AODEventContent.outputCommands,
   compressionLevel = cms.untracked.int32(7)
)

process.MiniOut4 = cms.OutputModule("PoolOutputModule",
   fileName = cms.untracked.string ("MergedWithItself_MiniAOD_l4.root"),
   outputCommands = process.MINIAODEventContent.outputCommands,
   compressionLevel = cms.untracked.int32(4)
)

process.MiniOut7 = cms.OutputModule("PoolOutputModule",
   fileName = cms.untracked.string ("MergedWithItself_MiniAOD_l7.root"),
   outputCommands = process.MINIAODEventContent.outputCommands,
   compressionLevel = cms.untracked.int32(7)
)

process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

process.end = cms.EndPath(process.Out4 + process.Out7 + process.MiniOut4 + process.MiniOut7)
