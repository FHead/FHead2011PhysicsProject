WorkDirectory = "~/work/PhysicsWorkspace/JetEnergyCorrection/JetStudies/17467_R45Investigation/"

# InputFile = "file:/eos/cms/store/data/Run2018C/SingleMuon/RAW/v1/000/319/524/00000/FE6A0B1A-8E85-E811-AC1C-FA163EEAACDE.root"
InputFile = "file:/eos/cms/store/data/Run2018C/JetHT/RAW/v1/000/319/524/00000/F881BA36-5C85-E811-8D6A-FA163E16A054.root"

defult: GrepLog

PrepareConfiguration:
	hltGetConfiguration run:319524 \
		--globaltag 101X_dataRun2_HLT_v7 \
		--process MyWonderfulHLT --full --offline --data \
		--unprescale --max-events 200 \
		--input $(InputFile) \
			> ExportedMenu.py
	echo "process.DQMHistograms = cms.EndPath( process.hltGtStage2Digis + process.hltScalersRawToDigi + process.hltTriggerRatesMonitor + process.hltTriggerBxMonitor + process.hltLumiMonitor )" >> ExportedMenu.py
	cp ExportedMenu.py ExportedMenuNoR45.py
	echo "process.hltHbhePhase1Reco.pulseShapeParametersQIE8.MinimumTS4TS5Threshold = cms.double(10000.0)" >> ExportedMenuNoR45.py
	cp ExportedMenu.py ExportedMenuTightR45.py
	echo "process.hltHbhePhase1Reco.pulseShapeParametersQIE8.TS4TS5LowerCut = cms.vdouble(0.1, 0.1, 0.1, 0.1, 0.1, 0.1)" >> ExportedMenuTightR45.py
	echo "process.hltHbhePhase1Reco.pulseShapeParametersQIE8.TS4TS5UpperCut = cms.vdouble(0.11, 0.11, 0.11, 0.11)" >> ExportedMenuTightR45.py
	cp ExportedMenu.py ExportedMenuSuperTightR45.py
	echo "process.hltHbhePhase1Reco.pulseShapeParametersQIE8.MinimumTS4TS5Threshold = cms.double(10.0)" >> ExportedMenuSuperTightR45.py
	echo "process.hltHbhePhase1Reco.pulseShapeParametersQIE8.TS4TS5LowerCut = cms.vdouble(0.1, 0.1, 0.1, 0.1, 0.1, 0.1)" >> ExportedMenuSuperTightR45.py
	echo "process.hltHbhePhase1Reco.pulseShapeParametersQIE8.TS4TS5UpperCut = cms.vdouble(0.11, 0.11, 0.11, 0.11)" >> ExportedMenuSuperTightR45.py


Execute:
	mkdir -p Reference/ Test/
	cmsRun ExportedMenu.py &> Reference.log
	mv run*stream* Reference/
	mv *root Reference/
	cmsRun ExportedMenuNoR45.py &> Test.log
	mv run*stream* Test/
	mv *root Test/

ExecuteTight:
	mkdir -p Tight/
	cmsRun ExportedMenuTightR45.py &> Tight.log
	mv run*stream* Tight/
	mv *root Tight/

ExecuteSuperTight:
	mkdir -p SuperTight/
	cmsRun ExportedMenuSuperTightR45.py &> SuperTight.log
	mv run*stream* SuperTight/
	mv *root SuperTight/

GrepLog:
	for i in Scenario*; do bzgrep TrigReport $$i/Log.bz2 | grep " HLT" | bzip2 > $$i/TrigReport.bz2; done

