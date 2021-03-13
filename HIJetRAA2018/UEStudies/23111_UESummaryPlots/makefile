default: TestRun

TestRun: Execute
	./Execute --MC MCFits.dh --MCEta MCReducedEtaFits.dh \
		--Data MCFits.dh --DataEta --MCFits.dh \
		--Output UE.pdf
	cp UE.pdf ~/public/html/

Execute: MakeSummaryPlots.cpp
	CompileRootMacro MakeSummaryPlots.cpp Execute




