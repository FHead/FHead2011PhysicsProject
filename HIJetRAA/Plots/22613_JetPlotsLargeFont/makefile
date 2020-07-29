default: TestRun

TestRun: Execute
	./Execute
	cp PlotJet.pdf ~/WindowsHome/Downloads/

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
