FileName=$1

#beamspot customization
echo "" >> $FileName
echo "import CalibTracker.Configuration.Common.PoolDBESSource_cfi" >> $FileName
echo "process.newBS = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'), toGet = cms.VPSet(cms.PSet(record = cms.string('BeamSpotObjectsRcd'), tag = cms.string('BeamSpotObjects_Realistic25ns_13TeVCollisions_Early2017_v1_mc'))))" >> $FileName
echo "process.prefer_PreferNewBS = cms.ESPrefer('PoolDBESSource', 'newBS')" >> $FileName

#muon customization (via Emilien)
echo "" >> $FileName
echo "process.simEmtfDigis.CSCInputBXShift = cms.int32(-6)" >> $FileName

#EG customization (via Kaya)
echo "" >> $FileName
echo "process.caloStage2Params.egBypassExtHOverE = cms.uint32(1)" >> $FileName
echo "process.caloStage2Params.egBypassShape = cms.uint32(1)" >> $FileName
echo "process.caloStage2Params.egBypassECALFG = cms.uint32(1)" >> $FileName
echo "process.caloStage2Params.egHOverEcutBarrel = cms.int32(1)" >> $FileName
echo "process.caloStage2Params.egHOverEcutEndcap = cms.int32(1)" >> $FileName
echo "process.caloStage2Params.egEtaCut = cms.int32(24)" >> $FileName

#Jet customization (via Chris)
echo "" >> $FileName
echo "process.caloStage2Params.hiMode = cms.uint32(1)" >> $FileName
echo "process.caloStage2Params.jetPUSType = cms.string('PhiRing2')" >> $FileName
echo "process.caloStage2Params.jetPUSUseChunkySandwich = cms.uint32(False)" >> $FileName

#Fix for hcal electroics map running on old digi
#believe this is related to issues running pre5 reco on digi from pre4 or earlier
#see twiki here: https://twiki.cern.ch/twiki/bin/view/CMS/HiHighPtRecoValidation2018#Starting_from_other_CMSSW_10_3_p
echo "" >> $FileName
echo "process.GlobalTag.toGet = cms.VPSet(cms.PSet(record = cms.string('HcalElectronicsMapRcd'), tag = cms.string('HcalElectronicsMap_2018_v3.0_mc'), connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'), globaltag=cms.string('103X_upgrade2018_realistic_v4')))" >> $FileName

#Fix for centrality based on branch hiUpdateSaturation here: https://github.com/bundocka/cmssw/blob/hiUpdateSaturation/L1Trigger/L1TCalorimeter/python/caloParams_2018_v1_4_cfi.py
echo "" >> $FileName
echo "process.caloStage2Params.etSumCentralityLower = cms.vdouble(0.0, 2.5,  13.5,  133.0, 411.5,  1101.5, 2494.5, 65535.0)" >> $FileName
echo "process.caloStage2Params.etSumCentralityUpper = cms.vdouble(8.0, 25.5, 208.0, 567.5, 1349.5, 2790.5, 5114.0, 65535.0)" >> $FileName

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

#Remove DQMIO output
# sed -i -e "s@process.DQMOutput @#process.DQMOutput @g" $FileName
