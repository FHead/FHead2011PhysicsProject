
default: RunSynchTest RunSynchFit

RunSynchTest:
	jet_synchtest_x `cat SifuJetSynchTest.config`

RunSynchFit:
	jet_synchfit_x `cat SifuJetSynchFit.config`

RunApplyL1Sifu:
	jet_apply_jec_x `cat SifuJetApplyL1.config`

RunApplyL1:
	jet_apply_jec_x -input Input/WithPU.root -jecpath ./ -era Magda -levels 1 -output Input/DontLook2.root -L1FastJet true

RunJRA:
	jet_response_analyzer_x jra.config `cat SifuJetResponseAnalyzer.config`

RunL2Correction:
	jet_l2_correction_x -input jra.root -era Sifu -l2l3 true -batch 1

RunClosure:
	jet_correction_analyzer_x -inputFilename Input/DontLook2.root -outputDir ./ -path ./ -era Sifu -levels 2 -algs ak4pfchsl1 -drmax 0.2
	jet_draw_closure_x -doPt true -doEta false -doRatioPt false -doRatioEta false -doFlavorDifference false -filename Closure_ak4pfchsl1 -ptcl false -algs ak4pfchsl1 -path ./ -histMet median -outputDir ./

RunDefaultClosure:
	jet_correction_analyzer_x -inputFilename Input/DontLook2.root -outputDir ./ -path ./ -era Fall17_17Nov2017_V8_MC -levels 2 -algs ak4pfchsl1 -drmax 0.2
	jet_draw_closure_x -doPt true -doEta false -doRatioPt false -doRatioEta false -doFlavorDifference false -filename Closure_ak4pfchsl1 -ptcl false -algs ak4pfchsl1 -path ./ -histMet median -outputDir ./

RunDefaultClosure123:
	jet_correction_analyzer_x -inputFilename Input/WithPU.root -outputDir ./ -path ./ -era Fall17_17Nov2017_V8_MC -levels 1 2 -algs ak4pfchs -drmax 0.2
	jet_draw_closure_x -doPt true -doEta false -doRatioPt false -doRatioEta false -doFlavorDifference false -filename Closure_ak4pfchs -ptcl false -algs ak4pfchs -path ./ -histMet median -outputDir ./

RunDefaultClosure23:
	jet_correction_analyzer_x -inputFilename Input/WithPU.root -outputDir ./ -path ./ -era Fall17_17Nov2017_V8_MC -levels 2 -algs ak4pfchs -drmax 0.2
	jet_draw_closure_x -doPt true -doEta false -doRatioPt false -doRatioEta false -doFlavorDifference false -filename Closure_ak4pfchs -ptcl false -algs ak4pfchs -path ./ -histMet median -outputDir ./




