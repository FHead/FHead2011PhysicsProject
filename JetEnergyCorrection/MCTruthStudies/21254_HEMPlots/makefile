default: RunAK4PF RunAK8PF

Execute: PlotJEC.cpp
	CompileRootMacro PlotJEC.cpp Execute

RunAK4PF: Execute
	./Execute \
		--jecl1 "Autumn18_V8_MC_L1FastJet_AK4PF.txt","Autumn18_V8_MC_L1FastJet_AK4PFchs.txt","2018_BadHEM/ak4pf/Fall18_25ns_MC_L1FastJet_AK4PF.txt","2018_BadHEM/ak4pfchs/Fall18_25ns_MC_L1FastJet_AK4PFchs.txt" \
		--jecl2l3 "Trivial.txt","Trivial.txt","Trivial.txt","Trivial.txt" \
		--label "Good HEM AK4PF","Good HEM AK4PFCHS","Bad HEM AK4PF","Bad HEM AK4PFCHS" \
		--output JEC_AK4PF.pdf --offset true

RunAK8PF: Execute
	./Execute \
		--jecl1 "Autumn18_V8_MC_L1FastJet_AK8PF.txt","Autumn18_V8_MC_L1FastJet_AK8PFchs.txt","2018_BadHEM/AK8pf/Fall18_25ns_MC_L1FastJet_AK8PF.txt","2018_BadHEM/AK8pfchs/Fall18_25ns_MC_L1FastJet_AK8PFchs.txt" \
		--jecl2l3 "Trivial.txt","Trivial.txt","Trivial.txt","Trivial.txt" \
		--label "Good HEM AK8PF","Good HEM AK8PFCHS","Bad HEM AK8PF","Bad HEM AK8PFCHS" \
		--output JEC_AK8PF.pdf --offset true


