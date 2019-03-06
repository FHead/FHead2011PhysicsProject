default: RunAK4PFCHS RunAK8PFCHS RunAK4PFPuppi RunAK8PFPuppi

Execute: PlotJEC.cpp
	CompileRootMacro PlotJEC.cpp Execute

RunAK4PFCHS: Execute
	./Execute \
		--jec "Autumn18_V2_MC_L2Relative_AK4PFchs.txt","Autumn18_V3_MC_L2Relative_AK4PFchs.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK4PFchs.txt","Summer16_07Aug2017_V20_MC_L2Relative_AK4PFchs.txt" \
		--label "Autumn18 V2","Autumn18 V3","Fall17 V32","Summer16 V20" \
		--output JEC_AK4PFCHS.pdf --offset false

RunAK8PFCHS: Execute
	./Execute \
		--jec "Autumn18_V3_MC_L2Relative_AK8PFchs.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK8PFchs.txt","Summer16_07Aug2017_V20_MC_L2Relative_AK8PFchs.txt" \
		--label "Autumn18 V3","Fall17 MC V33","Summer16 V20" \
		--output JEC_AK8PFCHS.pdf --offset false

RunAK4PFPuppi: Execute
	./Execute \
		--jec "Autumn18_V2_MC_L2Relative_AK4PFPuppi.txt","Autumn18_V3_MC_L2Relative_AK4PFPuppi.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK4PFPuppi.txt","Summer16_07Aug2017_V20_MC_L2Relative_AK4PFPuppi.txt" \
		--label "Autumn18 V2","Autumn18 V3","Fall17 V32","Summer16 V20" \
		--output JEC_AK4PFPuppi.pdf --offset false

RunAK8PFPuppi: Execute
	./Execute \
		--jec "Autumn18_V3_MC_L2Relative_AK8PFPuppi.txt","Fall17_17Nov2017_V32_MC_L2Relative_AK8PFPuppi.txt","Summer16_07Aug2017_V20_MC_L2Relative_AK8PFPuppi.txt" \
		--label "Autumn18 V3","Fall17 MC V33","Summer16 V20" \
		--output JEC_AK8PFPuppi.pdf --offset false



