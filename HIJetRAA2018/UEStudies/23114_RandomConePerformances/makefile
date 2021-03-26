default: TestRun

TestRunMC: Execute
	time ./Execute --input RandomConeTrees/ResultMC.root \
		--output MCPlots.pdf --dhfile MCFits.dh
	cp *pdf ~/public/html/

TestRunData: Execute
	time ./Execute --input RandomConeTrees/ResultData.root \
		--output DataPlots.pdf --dhfile DataFits.dh
	cp *pdf ~/public/html/

Execute: PlotPerformances.cpp
	CompileRootMacro PlotPerformances.cpp Execute
