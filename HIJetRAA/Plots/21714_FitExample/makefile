default: TestRun

TestRun: Execute
	mkdir -p plots
	./Execute

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
