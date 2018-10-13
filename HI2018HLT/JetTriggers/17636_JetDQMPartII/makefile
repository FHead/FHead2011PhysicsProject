default:
	echo Meow

RunStep0:
	cmsDriver.py step0 -s HLT:PFJetV10 \
		--conditions auto:run2_mc_GRun --mc \
		--eventcontent FEVTDEBUGHLT \
		--hltProcess reHLT \
		--filein file:SamplesTTbar/step1_DIGI_L1_DIGI2RAW_HLT_PU_356.root \
		--processName=reHLT \
		--era Run2_2018_pp_on_AA \
		-n 100

RunStep1:
	cmsDriver.py step1 -s RAW2DIGI,L1Reco,RECO,EI,DQM \
		--eventcontent DQM --datatier DQMIO \
		--conditions 103X_upgrade2018_realistic_HI_v2 \
		--mc --process reRECO \
		--filein file:step0_HLT.root \
		--era Run2_2018_pp_on_AA \
		-n 100

RunWorkflow158Part1:
	cmsDriver.py step2  --conditions auto:phase1_2018_realistic -s DIGI:pdigi_hi,L1,DIGI2RAW,HLT:PFJetV10 --datatier GEN-SIM-DIGI-RAW-HLTDEBUG --pileup HiMixNoPU -n -1 --era Run2_2018_pp_on_AA --eventcontent FEVTDEBUGHLT --filein file:SamplesTTbar/step1_DIGI_L1_DIGI2RAW_HLT_PU_356.root

RunWorkflow158Part2:
	cmsDriver.py step3  --runUnscheduled \
		--conditions auto:phase1_2018_realistic \
		-s RAW2DIGI,L1Reco,RECO,EI,PAT,DQM:@standardDQM+@ExtraHLT+@miniAODDQM \
		--datatier DQMIO -n -1 --era Run2_2018_pp_on_AA \
		--eventcontent DQM --filein file:step0_HLT.root --mc

RunWorkflow158Part2Variant:
	cmsDriver.py step3  --runUnscheduled \
		--conditions auto:phase1_2018_realistic \
		-s RAW2DIGI,L1Reco,RECO,EI,PAT,DQM \
		--datatier DQMIO -n -1 --era Run2_2018_pp_on_AA \
		--eventcontent DQM --filein file:step0_HLT.root --mc

RunWorkflow158Part3:
	cmsDriver.py step4  --conditions auto:phase1_2018_realistic -s HARVESTING:dqmHarvesting --filetype DQM -n -1 --era Run2_2018_pp_on_AA --mc --filein file:step3_RAW2DIGI_L1Reco_RECO_EI_PAT_DQM.root



