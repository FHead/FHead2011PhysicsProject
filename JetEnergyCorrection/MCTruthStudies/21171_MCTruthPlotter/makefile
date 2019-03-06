default: RunAK4PF RunAK4PFCHS RunAK8PF RunAK8PFCHS

Execute: PlotJEC.cpp
	CompileRootMacro PlotJEC.cpp Execute

RunAK4PF: Execute
	./Execute \
		--jec "ak4pf/ak4/Fall18_25ns_MC_L1FastJet_AK4PF.txt","ak4pf/ak4_test/Fall18_25ns_MC_L1FastJet_AK4PF.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK4PF.txt"\
		--label "Original","Extra terms","Fall17 MC V32" \
		--output JEC_AK4PF.pdf --offset true

RunAK4PFCHS: Execute
	./Execute \
		--jec "ak4pfchs/ak4/Fall18_25ns_MC_L1FastJet_AK4PFchs.txt","ak4pfchs/ak4_test/Fall18_25ns_MC_L1FastJet_AK4PFchs.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK4PFchs.txt"\
		--label "Original","Extra terms","Fall17 MC V32" \
		--output JEC_AK4PFCHS.pdf --offset true

RunAK8PF: Execute
	./Execute \
		--jec "ak8pf/ak8/Fall18_25ns_MC_L1FastJet_ak8PF.txt","ak8pf/ak8_test/Fall18_25ns_MC_L1FastJet_ak8PF.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK8PF.txt"\
		--label "Original","Extra terms","Fall17 MC V32" \
		--output JEC_AK8PF.pdf --offset true

RunAK8PFCHS: Execute
	./Execute \
		--jec "ak8pfchs/ak8/Fall18_25ns_MC_L1FastJet_ak8PFchs.txt","ak8pfchs/ak8_test/Fall18_25ns_MC_L1FastJet_ak8PFchs.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK8PFchs.txt"\
		--label "Original","Extra terms","Fall17 MC V32" \
		--output JEC_AK8PFCHS.pdf --offset true

RunAK4: Execute
	./Execute \
		--jec "ak4pf/ak4/Fall18_25ns_MC_L1FastJet_AK4PF.txt","ak4pfchs/ak4/Fall18_25ns_MC_L1FastJet_AK4PFchs.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK4PF.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK4PFchs.txt","Summer16_07Aug2017_V20_MC_L1FastJet_AK4PF.txt","Summer16_07Aug2017_V20_MC_L1FastJet_AK4PFchs.txt"\
		--label "Autumn18 AK4PF","Autumn18 AK4PFCHS","Fall17 V32 AK4PF","Fall17 V32 AK4PFCHS","Summer16 V20 AK4PF","Summer16 V20 AK4PFCHS" \
		--output JEC_AK4.pdf --offset true

