default: TestRun

TestRun: Execute
	./Execute
	cp PlotSystematics.pdf ~/public/html/

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
