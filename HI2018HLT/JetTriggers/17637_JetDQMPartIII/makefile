default:
	ln -s /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/ikucher/TTbar_5020GeV_TuneCUETP8M1_DIGI_L1_DIGI2RAW_HLT_PU/TTbar_5020GeV_TuneCUETP8M1_GEN_SIM_PU/crab_TTbar_5020GeV_TuneCUETP8M1_DIGI_L1_DIGI2RAW_HLT_PU/180724_211145/0000// SamplesTTbar

RunStep0:
	cmsDriver.py step0 -s HLT:CaloJetV4 \
		--conditions auto:run2_mc_GRun --mc \
		--eventcontent FEVTDEBUGHLT \
		--hltProcess reHLT \
		--filein file:SamplesTTbar/step1_DIGI_L1_DIGI2RAW_HLT_PU_356.root \
		--processName=reHLT \
		--era Run2_2018_pp_on_AA \
		-n 100

RunStep0PP:
	cmsDriver.py step0 -s HLT:CaloJetV4 \
		--conditions auto:run2_mc_GRun --mc \
		--eventcontent FEVTDEBUGHLT \
		--hltProcess reHLT \
		--filein file:/eos/cms/store/cmst3/user/chenyi///6FA0B561-A9C5-024B-A18D-45A0C31DE131.root \
		--processName=reHLT \
		-n 100


RunStep1:
	cmsDriver.py step1 -s RAW2DIGI,L1Reco,RECO,EI,PAT,DQM:@standardDQM+@ExtraHLT+@HLTMon  --runUnscheduled \
		--eventcontent DQM --datatier DQMIO \
		--mc --process reRECO \
		--filein file:step0_HLT.root \
		--conditions auto:phase1_2018_realistic \
		-n 100

RunStep2:
	cmsDriver.py step2 -s HARVESTING:dqmHarvesting --harvesting AtRunEnd \
		--conditions auto:phase1_2018_realistic --geometry DB:Extended \
		--mc --scenario pp \
		--filein file:step1_RAW2DIGI_L1Reco_RECO_EI_PAT_DQM.root --filetype DQM \
		-n -1

RunLegacy:
	cmsDriver.py step5 -s RAW2DIGI,L1Reco,RECO,HLT:CaloJetV4,EI,DQM \
		--conditions auto:run2_mc_GRun --mc \
		--eventcontent FEVTDEBUGHLT \
		--hltProcess reHLT \
		--filein root://xrootd.cmsaf.mit.edu//store/user/gsfs/Pythia8_TTBar_pp_CUETP8M1_5020GeV/RAW_20171007/171009_115554/0000/step2_pp_DIGI_L1_DIGI2RAW_HLT_1.root \
		--processName=reHLT \
		-n 100

RunWorkflow158Part1:
	cmsDriver.py step2  --conditions auto:phase1_2018_realistic -s DIGI:pdigi_hi,L1,DIGI2RAW,HLT:CaloJetV4 --datatier GEN-SIM-DIGI-RAW-HLTDEBUG --pileup HiMixNoPU -n -1 --era Run2_2018_pp_on_AA --eventcontent FEVTDEBUGHLT --filein file:SamplesTTbar/step1_DIGI_L1_DIGI2RAW_HLT_PU_356.root

RunWorkflow158Part1PP:
	cmsDriver.py step2  --conditions auto:phase1_2018_realistic -s DIGI:pdigi_hi,L1,DIGI2RAW,HLT:CaloJetV4 --datatier GEN-SIM-DIGI-RAW-HLTDEBUG --pileup HiMixNoPU -n -1 --era Run2_2018_pp_on_AA --eventcontent FEVTDEBUGHLT --filein file:/eos/cms/store/cmst3/user/chenyi///6FA0B561-A9C5-024B-A18D-45A0C31DE131.root

RunWorkflow158Part2:
	cmsDriver.py step3  --runUnscheduled \
		--conditions 103X_upgrade2018_realistic_HI_v5 \
		-s RAW2DIGI,L1Reco,RECO,EI,PAT,DQM:@standardDQM+@ExtraHLT+@HLTMon+@miniAODDQM \
		--datatier DQMIO -n 1  --era Run2_2018_pp_on_AA \
		--scenario HeavyIons \
		--eventcontent DQM --filein file:step0_HLT.root --mc

RunWorkflow158Part2Variant:
	cmsDriver.py step3  --runUnscheduled \
		--conditions 103X_upgrade2018_realistic_HI_v5 \
		-s RAW2DIGI,L1Reco,RECO,EI,PAT,DQM \
		--datatier DQMIO -n -1 --era Run2_2018_pp_on_AA \
		--scenario HeavyIons \
		--eventcontent DQM --filein file:step0_HLT.root --mc

RunWorkflow158Part3:
	cmsDriver.py step4  --conditions auto:phase1_2018_realistic -s HARVESTING:dqmHarvesting --filetype DQM -n -1 --era Run2_2018_pp_on_AA --mc --filein file:step3_RAW2DIGI_L1Reco_RECO_EI_PAT_DQM.root


RunWorkflow150Part2:
	cmsDriver.py step3  --runUnscheduled \
		--conditions 103X_upgrade2018_realistic_HI_v5 \
		-s RAW2DIGI,L1Reco,RECO,DQM \
		--datatier DQMIO -n -1 --era Run2_2018 \
		--scenario HeavyIons \
		--eventcontent DQM --filein file:step0_HLT.root 

RunWorkflow150Part2Variant:
	cmsDriver.py step3  --runUnscheduled \
		--conditions 103X_upgrade2018_realistic_HI_v5 \
		-s RAW2DIGI,L1Reco,RECO,DQM:@HLTMon+@ExtraHLT \
		--datatier DQMIO -n -1 --era Run2_2018 \
		--scenario HeavyIons \
		--eventcontent DQM --filein file:step0_HLT.root 

RunWorkflow150Part3:
	cmsDriver.py step4  --conditions auto:phase1_2018_realistic -s HARVESTING:dqmHarvesting --scenario HeavyIons --filetype DQM -n 2 --era Run2_2018 --mc --filein file:step3_RAW2DIGI_L1Reco_RECO_DQM.root

