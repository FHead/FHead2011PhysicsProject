default: TestRun

TestRun: Execute
	./Execute
	cp PlotJet.pdf ~/public/html/

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
