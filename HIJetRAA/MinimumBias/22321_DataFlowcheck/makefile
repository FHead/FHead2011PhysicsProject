



default: TestRunPlot

TestRunPlot: ExecutePlot
	./ExecutePlot
	cp *pdf ~/public/html/

TestRun: Execute
	./Execute

ExecutePlot: MakePlot.cpp
	CompileRootMacro MakePlot.cpp ExecutePlot

Execute: FlowCheck.cpp
	CompileRootMacro FlowCheck.cpp Execute

