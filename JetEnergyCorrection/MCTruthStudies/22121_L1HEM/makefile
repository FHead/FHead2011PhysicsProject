default: TestRun

TestRun: Execute
	time ./Execute --input HEMSamples/AllResult_PF.root --output PF.pdf \
<<<<<<< HEAD
		--goodinput HealthySamples/AllResult_PF.root --etamin -2.0 --etamax -1.5
	time ./Execute --input HEMSamples/AllResult_PFCHS.root --output PFCHS.pdf \
		--goodinput HealthySamples/AllResult_PFCHS.root --etamin -2.0 --etamax -1.5
=======
		--goodinput HealthySamples/AllResult_PF.root --etamin -3.0 --etamax -1.5
	time ./Execute --input HEMSamples/AllResult_PFCHS.root --output PFCHS.pdf \
		--goodinput HealthySamples/AllResult_PFCHS.root --etamin -3.0 --etamax -1.5
>>>>>>> 20a61a6d943edf086cf1bb5d81e2b659a31a8bed
	cp *.pdf ~/public/html

Execute: HEML1.cpp
	CompileRootMacro HEML1.cpp Execute
