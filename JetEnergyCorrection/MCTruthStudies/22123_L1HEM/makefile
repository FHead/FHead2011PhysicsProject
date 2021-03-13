default: TestRun

TestRun: Execute
	time ./Execute --input HEMSamples/AllResult_PFCHS.root --output PFCHS.pdf \
		--goodinput HealthySamples/AllResult_PFCHS.root --etamin -3.0 --etamax -1.5 \
		--jec Autumn18_V19_MC_L1FastJet_AK4PFchs.txt --goodjec Autumn18_V19_MC_L1FastJet_AK4PFchs.txt
	cp *.pdf ~/public/html

Execute: HEML1.cpp
	CompileRootMacro HEML1.cpp Execute
