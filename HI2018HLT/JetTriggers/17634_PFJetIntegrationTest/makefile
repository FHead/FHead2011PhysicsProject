TestPF:
	hltIntegrationTests /users/chenyi/PbPb2018/HighPTJetsPbPb2018PFRestructure/V9 -s /dev/CMSSW_10_1_0/GRun --mc -i file:/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/ikucher/TTbar_5020GeV_TuneCUETP8M1_DIGI_L1_DIGI2RAW_HLT_PU/TTbar_5020GeV_TuneCUETP8M1_GEN_SIM_PU/crab_TTbar_5020GeV_TuneCUETP8M1_DIGI_L1_DIGI2RAW_HLT_PU/180724_211145/0000/step1_DIGI_L1_DIGI2RAW_HLT_PU_10.root -x "--l1-emulator FullMC --l1Xml L1Menu_CollisionsHeavyIons2018_v3_Fix2.xml --customise HLTrigger/Configuration/customizeHLTforCMSSW.customiseFor2017DtUnpacking --globaltag auto:run2_mc_GRun --full --offline"

TestCalo:
	rm -rf hltintegration
	hltIntegrationTests /users/chenyi/PbPb2018/HighPTJetsPbPb2018CaloOnly/V4 \
		-s /dev/CMSSW_10_1_0/GRun --mc \
		-i file:/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/ikucher/Dijet100_TuneZ2_5020GeV_DIGI_L1_DIGI2RAW_HLT_PU/Dijet100_TuneZ2_5020GeV_GEN_SIM_PU/crab_Dijet100_TuneZ2_5020GeV_DIGI_L1_DIGI2RAW_HLT_PU/180827_202726/0000/step1_DIGI_L1_DIGI2RAW_HLT_PU_3.root \
		-x "--l1-emulator FullMC --l1Xml L1Menu_CollisionsHeavyIons2018_v3.xml --customise HLTrigger/Configuration/customizeHLTforCMSSW.customiseFor2017DtUnpacking --globaltag auto:run2_mc_GRun --full --offline"


