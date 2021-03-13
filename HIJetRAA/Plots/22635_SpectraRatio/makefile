default: TestRun

TestRun: Execute
	./Execute
	cp *pdf ~/public/html/

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
