default: RunAK4PFPuppi RunAK4PFCHS RunAK8PFPuppi RunAK8PFCHS

Execute: PlotJEC.cpp
	CompileRootMacro PlotJEC.cpp Execute

RunAK4PF: Execute
	./Execute \
		--jecl1 "Summer16_07Aug2017_V20_MC_L1FastJet_AK4PF.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK4PF.txt","Autumn18_V1_MC_L1FastJet_AK4PF.txt" \
		--jecl2l3 "Summer16_07Aug2017_V20_MC_L2Relative_AK4PF.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK4PF.txt","Autumn18_V1_MC_L2Relative_AK4PF.txt" \
		--label "Summer16 V20","Fall17 V32","Autumn18" \
		--output JEC_AK4PF.pdf --offset false

RunAK4PFCHS: Execute
	./Execute \
		--jecl1 "Summer16_07Aug2017_V20_MC_L1FastJet_AK4PFchs.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK4PFchs.txt","Autumn18_V1_MC_L1FastJet_AK4PFchs.txt" \
		--jecl2l3 "Summer16_07Aug2017_V20_MC_L2Relative_AK4PFchs.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK4PFchs.txt","Autumn18_V1_MC_L2Relative_AK4PFchs.txt" \
		--label "Summer16 V20","Fall17 V32","Autumn18" \
		--output JEC_AK4PFCHS.pdf --offset false

RunAK4PFPuppi: Execute
	./Execute \
		--jecl1 "Summer16_07Aug2017_V20_MC_L1FastJet_AK4PFPuppi.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK4PFPuppi.txt","Autumn18_V1_MC_L1FastJet_AK4PFPuppi.txt" \
		--jecl2l3 "Summer16_07Aug2017_V20_MC_L2Relative_AK4PFPuppi.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK4PFPuppi.txt","Autumn18_V1_MC_L2Relative_AK4PFPuppi.txt" \
		--label "Summer16 V20","Fall17 V32","Autumn18" \
		--output JEC_AK4PFPuppi.pdf --offset false

RunAK8PF: Execute
	./Execute \
		--jecl1 "Summer16_07Aug2017_V20_MC_L1FastJet_AK8PF.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK8PF.txt","Autumn18_V1_MC_L1FastJet_AK8PF.txt" \
		--jecl2l3 "Summer16_07Aug2017_V20_MC_L2Relative_AK8PF.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK8PF.txt","Autumn18_V1_MC_L2Relative_AK8PF.txt" \
		--label "Summer16 V20","Fall17 V32","Autumn18" \
		--output JEC_AK8PF.pdf --offset false

RunAK8PFCHS: Execute
	./Execute \
		--jecl1 "Summer16_07Aug2017_V20_MC_L1FastJet_AK8PFchs.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK8PFchs.txt","Autumn18_V1_MC_L1FastJet_AK8PFchs.txt" \
		--jecl2l3 "Summer16_07Aug2017_V20_MC_L2Relative_AK8PFchs.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK8PFchs.txt","Autumn18_V1_MC_L2Relative_AK8PFchs.txt" \
		--label "Summer16 V20","Fall17 V32","Autumn18" \
		--output JEC_AK8PFCHS.pdf --offset false

RunAK8PFPuppi: Execute
	./Execute \
		--jecl1 "Summer16_07Aug2017_V20_MC_L1FastJet_AK8PFPuppi.txt","Fall17_17Nov2017_V32_MC_L1FastJet_AK8PFPuppi.txt","Autumn18_V1_MC_L1FastJet_AK8PFPuppi.txt" \
		--jecl2l3 "Summer16_07Aug2017_V20_MC_L2Relative_AK8PFPuppi.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK8PFPuppi.txt","Autumn18_V1_MC_L2Relative_AK8PFPuppi.txt" \
		--label "Summer16 V20","Fall17 V32","Autumn18" \
		--output JEC_AK8PFPuppi.pdf --offset false

