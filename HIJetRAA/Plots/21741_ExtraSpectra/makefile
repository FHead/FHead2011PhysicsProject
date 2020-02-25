default: TestRun

TestRun: Execute
	./Execute --R 2
	./Execute --R 3
	./Execute --R 4
	./Execute --R 6
	./Execute --R 8
	./Execute --R 10

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
