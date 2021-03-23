default: TestRun

TestRun: Execute
	mkdir -p plots
	./Execute --Run 262620 --Lumi 99 --Event 4344653
	cp plots/PlotJet_Run262620_Lumi99_Evt4344653_hiBin27.pdf ~/WindowsHome/Downloads/

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
