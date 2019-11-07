default: TestRun

TestRun: Execute
	./Execute --C 0
	./Execute --C 1
	./Execute --C 2
	./Execute --C 3

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
