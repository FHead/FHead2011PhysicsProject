
Execute: Transcribe.cpp JetCorrector.h
	CompileRootMacro Transcribe.cpp Execute

RunTestJetCorrector: TestJetCorrector.cpp
	CompileRootMacro TestJetCorrector.cpp RunTestJetCorrector

TestRun: Execute
	time ./Execute \
		-input /eos/cms/store/group/phys_jetmet/magda/AK4chs_PU_GT/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/PU2017/180306_134748/0003/JRA_3300.root \
		-output SimpleTree.root \
		-tree ak4pfchs/t \
		-l1 Fall17_17Nov2017_V8_MC_L1FastJet_AK4PFchs.txt \
		-l2l3 Fall17_17Nov2017_V8_MC_L2Relative_AK4PFchs.txt

