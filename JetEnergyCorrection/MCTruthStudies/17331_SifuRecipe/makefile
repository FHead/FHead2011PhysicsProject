
RunSynchTest:
	jet_synchtest_x \
		-basepath ./Input/ \
		-samplePU WithPU.root \
		-sampleNoPU NoPU.root \
		-algo1 ak4pfchs \
		-algo2 ak4pfchs \
		-iftest false \
		-maxEvts 10000000 \
		-ApplyJEC false \
		-outputPath ./Correction/ \
		-npvRhoNpuBinWidth 10 \
		-NBinsNpvRhoNpu 6 \
		-MCPUReWeighting PUReweighting/MyMCPileupHistogram.root \
		-DataPUReWeighting PUReweighting/MyDataPileupHistogram.root \
		-useweight true \
		-nrefmax 3 \
		-doNotSave false

RunSynchFit:
	jet_synchfit_x \
		-inputDir  Correction/ \
		-outputDir Correction/ \
		-algo1 ak4pfchs \
		-algo2 ak4pfchs \
		-highPU false \
		-useNPU false \
		-functionType standard \
		-era SmallSampleForL1_MC

RunDeriveL1:
	##############################################################################
	##### Steps: set fixpar2 = false and run this                            #####
	#####    insert the parameters back and set fixpar2 = true and run again #####
	##############################################################################
	root -l -b -q deriveL1.C

RunApplyL1:
	jet_apply_jec_x \
		-input Input/WithPU.root \
		-output Input/JRA_jecl1.root \
		-jecpath Correction \
		-era SmallSample_MC \
		-levels 1 \
		-algs ak4pfchs \
		-L1FastJet true \
		-saveitree false

RunJRA:
	cp $(CMSSW_BASE)/src/JetMETAnalysis/JetAnalyzers/config/jra_dr_finebinning.config jra.config
	jet_response_analyzer_x jra.config \
		-input Input/JRA_jecl1.root \
		-nbinsabsrsp 0 \
		-nbinsetarsp 0 \
		-nbinsphirsp 0 \
		-nbinsrelrsp 200 \
		-doflavor false \
		-flavorDefinition phys \
		-MCPUReWeighting Input/PUReweighting/MyMCPileupHistogram.root \
		-MCPUHistoName pileup \
		-DataPUReWeighting Input/PUReweighting/MyDataPileupHistogram.root \
		-DataPUHistoName pileup \
		-output Input/jra.root \
		-useweight true \
		-nrefmax 3 \
		-algs ak4pfchsl1 \
		-drmax 0.2 \
		-relrspmin 0.0 \
		-relrspmax 2.0

RunL2Correction:
	jet_l2_correction_x \
		-input Input/jra.root \
		-algs ak4pfchsl1 \
		-era SmallSample_MC \
		-output l2.root \
		-outputDir Correction/ \
		-makeCanvasVariable AbsCorVsJetPt:JetEta \
		-l2l3 true \
		-batch true \
		-histMet median \
		-delphes false \
		-maxFitIter 30 \
		-l2calofit DynamicMin \
		-l2pffit splineAkima \
		-ptclip 20

RunCorrectionAnalyzer:
	ln -sf Correction/SmallSample_MC_L2Relative_AK4PFchsl1.txt Correction/SmallSample_MC_L2Relative_AK4PFchs.txt
	jet_correction_analyzer_x \
		-inputFilename Input/WithPU.root \
		-outputDir Correction/ \
		-path Correction/ \
		-era SmallSample_MC \
		-levels 1 2 \
		-useweight true \
		-algs ak4pfchs \
		-drmax 0.2 \
		-evtmax 0 \
		-nbinsrelrsp 200 \
		-relrspmin 0.0 \
		-relrspmax 2.0 \
		-MCPUReWeighting Input/PUReweighting/MyMCPileupHistogram.root \
		-DataPUReWeighting Input/PUReweighting/MyDataPileupHistogram.root \
		-nrefmax 3

RunDrawClosure:
	jet_draw_closure_x \
		-doPt true \
		-doEta false \
		-path Correction/ \
		-filename Closure_ak4pfchs \
		-histMet median \
		-outputDir Correction/ \
		-outputFormat .pdf \
		-draw_guidelines true \
		-doRatioPt false \
		-doRatioEta false




