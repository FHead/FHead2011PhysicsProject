default: TestRun

TestRun: Execute
	./Execute --MC MCFits.dh --Data DataFits.dh --Output SlowUE.pdf
	./Execute --MC NewMCFits.dh --Data NewDataFits.dh --Output UE.pdf
	cp UE.pdf ~/public/html/

Execute: MakeSummaryPlots.cpp
	CompileRootMacro MakeSummaryPlots.cpp Execute




