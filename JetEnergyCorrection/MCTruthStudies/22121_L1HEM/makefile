default: TestRun

TestRun: Execute
	time ./Execute --input HEMSamples/AllResult_PF.root --output PF.pdf \
		--goodinput HealthySamples/AllResult_PF.root --etamin -3.0 --etamax -1.5
	time ./Execute --input HEMSamples/AllResult_PFCHS.root --output PFCHS.pdf \
		--goodinput HealthySamples/AllResult_PFCHS.root --etamin -3.0 --etamax -1.5
	cp *.pdf ~/public/html

Execute: HEML1.cpp
	CompileRootMacro HEML1.cpp Execute
