default: TestRun

Execute: MakePlots.cpp
	CompileRootMacro MakePlots.cpp Execute

TestRun: Execute
	./Execute
	cp Output.pdf ~/public/html/
