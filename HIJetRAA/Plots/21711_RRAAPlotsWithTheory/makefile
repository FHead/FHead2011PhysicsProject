default: TestRun

TestRun: Execute
	./Execute --DoTheory false
	./Execute --DoTheory true

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
