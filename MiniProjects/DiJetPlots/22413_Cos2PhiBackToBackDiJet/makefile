

default: TestRun TestRunPlot

Execute: SmearingCheck.cpp
	CompileRootMacro SmearingCheck.cpp Execute

ExecutePlot: MakePlot.cpp
	CompileRootMacro MakePlot.cpp ExecutePlot

TestRun: Execute
	time ./Execute | TextToTree Tree.root 8 "PT0:PT1:PT2:Phi1:Phi2:Phi:QT:PT"

TestRunPlot: ExecutePlot
	time ./ExecutePlot
	cp Toy.pdf ~/public/html/
