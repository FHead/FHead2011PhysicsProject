FileName=$1

hltStr=MyMarvelousHLT

#beamspot customization
echo "" >> $FileName
echo "import CalibTracker.Configuration.Common.PoolDBESSource_cfi" >> $FileName
echo "process.newBS = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'), toGet = cms.VPSet(cms.PSet(record = cms.string('BeamSpotObjectsRcd'), tag = cms.string('BeamSpotObjects_Realistic25ns_13TeVCollisions_Early2017_v1_mc'))))" >> $FileName
echo "process.prefer_PreferNewBS = cms.ESPrefer('PoolDBESSource', 'newBS')" >> $FileName

#muon customization (via Emilien)
# echo "" >> $FileName
# echo "process.simEmtfDigis.CSCInputBXShift = cms.int32(-6)" >> $FileName

#Jet customization (via Chris)
echo "" >> $FileName
echo "process.caloStage2Params.hiMode = cms.uint32(1)" >> $FileName
#Temporary LUT override until correct LUT is uploaded
echo "process.caloStage2Params.jetCalibrationLUTFile = cms.FileInPath('L1Trigger/L1TCalorimeter/data/lut_calib_2018v1_ECALZS_noHFJEC.txt')" >> $FileName

#EG Spike killer customization (via Chris/Kaya)
echo "" >> $FileName
echo "process.simEcalTriggerPrimitiveDigis = cms.EDProducer('EcalTrigPrimProducer', BarrelOnly = cms.bool(False), Debug = cms.bool(False), Famos = cms.bool(False), InstanceEB = cms.string('ebDigis'), InstanceEE = cms.string('eeDigis'), Label = cms.string('unpackEcal'), TcpOutput = cms.bool(False), binOfMaximum = cms.int32(6))" >> $FileName
echo "" >> $FileName
echo "process.simCaloStage2Layer1Digis.ecalToken = cms.InputTag('simEcalTriggerPrimitiveDigis')" >> $FileName
echo "" >> $FileName
echo "process.SimL1Emulator = cms.Sequence(process.unpackRPC+process.unpackDT+process.unpackCSC+process.unpackEcal+process.unpackHcal+process.simHcalTriggerPrimitiveDigis+process.simEcalTriggerPrimitiveDigis+((process.simCaloStage2Layer1Digis+process.simCaloStage2Digis)+((process.simDtTriggerPrimitiveDigis+process.simCscTriggerPrimitiveDigis)+process.simTwinMuxDigis+process.simBmtfDigis+process.simEmtfDigis+process.simOmtfDigis+process.simGmtCaloSumDigis+process.simGmtStage2Digis)+(process.simGtExtFakeStage2Digis)+process.SimL1TGlobal)+process.packCaloStage2+process.packGmtStage2+process.packGtStage2+process.rawDataCollector)" >> $FileName
strGTtoGet1="cms.PSet(record = cms.string('EcalTPGFineGrainStripEERcd'), tag = cms.string('EcalTPGFineGrainStrip_12'), connect =cms.string('frontier://FrontierPrep/CMS_CONDITIONS')), cms.PSet(record = cms.string('EcalTPGSpikeRcd'), tag = cms.string('EcalTPGSpike_12'), connect =cms.string('frontier://FrontierPrep/CMS_CONDITIONS'))"
strGTtoGet=$strGTtoGet1

#Fix for hcal electroics map running on old digi
#believe this is related to issues running pre5 reco on digi from pre4 or earlier
#see twiki here: https://twiki.cern.ch/twiki/bin/view/CMS/HiHighPtRecoValidation2018#Starting_from_other_CMSSW_10_3_p
#DO NOT DO THE NEXT TWO LINES IF YOUR RAW/DIGI is 1030pre5 OR LATER
# strGTtoGet2="cms.PSet(record = cms.string('HcalElectronicsMapRcd'), tag = cms.string('HcalElectronicsMap_2018_v3.0_mc'), connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'), globaltag=cms.string('103X_upgrade2018_realistic_v4'))" #IF YOU FAIL PROCESSING RAW/DIGI 1030pre5 OR LATER THIS IS THE LIKELY CAUSE
# strGTtoGet=$strGTtoGet1", "$strGTtoGet2

## custom GT for Spike Killer and/or Hcal electronics map
echo "" >> $FileName
echo "process.GlobalTag.toGet = cms.VPSet(${strGTtoGet})" >> $FileName

#Adding hltbitanalyzer
echo "" >> $FileName
echo "process.load('HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi')" >> $FileName
echo "process.hltbitanalysis.HLTProcessName = cms.string('$hltStr')" >> $FileName
echo "process.hltbitanalysis.hltresults = cms.InputTag('TriggerResults', '', '$hltStr')" >> $FileName
echo "process.hltbitanalysis.l1results = cms.InputTag('hltGtStage2Digis', '', '$hltStr')" >> $FileName
echo "process.hltbitanalysis.UseTFileService = cms.untracked.bool(True)" >> $FileName
echo "process.hltbitanalysis.RunParameters = cms.PSet(isData = cms.untracked.bool(True))" >> $FileName
echo "process.hltBitAnalysis = cms.EndPath(process.hltbitanalysis)" >> $FileName
echo "process.TFileService = cms.Service('TFileService', fileName=cms.string('openHLT.root'))" >> $FileName

