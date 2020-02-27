default: TestRun

TestRun: Execute
	./Execute --DoTheory true
	./Execute --DoTheory false

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
