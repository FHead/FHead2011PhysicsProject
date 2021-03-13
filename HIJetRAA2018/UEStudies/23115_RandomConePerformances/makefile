default: TestRun

TestRun: Execute
	# time ./Execute --input RandomConeTrees/ResultMC_Rerun.root --output MCPlots.pdf --dhfile MCFits.dh
	time ./Execute --input RandomConeTrees/ResultData.root --output DataPlots.pdf --dhfile DataFits.dh

Execute: PerformFits.cpp
	CompileRootMacro PerformFits.cpp Execute -I../../CommonCode/include ../../CommonCode/library/Messenger.o
