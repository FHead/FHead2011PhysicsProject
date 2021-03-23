default: TestRun

TestRun: Execute
	# ./Execute --input RandomConeTrees/ResultMC.root \
	# 	--output MCPlots.pdf --plotdump AllMCPlots.pdf --dhfile MCFits.dh
	./Execute --input RandomConeTrees/ResultMC_ReducedEta.root \
		--output MCReducedEtaPlots.pdf --plotdump AllMCReducedEtaPlots.pdf --dhfile MCReducedEtaFits.dh
	cp *pdf ~/public/html/

Execute: PlotPerformances.cpp
	CompileRootMacro PlotPerformances.cpp Execute
