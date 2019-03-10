
Execute: Transcribe.cpp JetCorrector.h
	CompileRootMacro Transcribe.cpp Execute

RunTestJetCorrector: TestJetCorrector.cpp
	CompileRootMacro TestJetCorrector.cpp RunTestJetCorrector

TestRun: Execute
	time ./Execute \
		-input /eos/cms/store/group/phys_heavyions/chenyi/MCTruth/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/RunIIFall17DRStdmix-FlatPU0to70_94X_mc2017_realistic_v10-v1/AODSIM/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/MCTruth2017WithPU/180525_193528/0000/JRA_123.root \
		-output SimpleTree.root \
		-tree ak4pfchs/t \
		-l1 Fall17_17Nov2017_V8_MC_L1FastJet_AK4PFchs.txt \
		-l2l3 Fall17_17Nov2017_V8_MC_L2Relative_AK4PFchs.txt

