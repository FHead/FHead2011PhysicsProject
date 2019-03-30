default: RunPlot

RunPlot: Execute
	./Execute
	cp DJetResult.pdf ~/public/html

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
