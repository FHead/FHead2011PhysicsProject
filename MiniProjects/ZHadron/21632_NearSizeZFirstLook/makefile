

default: TestRunPlots

TestRun: Execute
	time ./Execute --Input vJetTrkSkim_pbpb_2018_data_zee.root --Output PlotsEE --EE true
	cp PlotsEE.pdf ~/public/html
	time ./Execute --Input vJetTrkSkim_pbpb_2018_data_zmm.root --Output PlotsMM --EE false
	cp PlotsMM.pdf ~/public/html/

TestRunPlots: ExecutePlot
	time ./ExecutePlot --Histogram HDPhiCent0030Subtracted --Output Meow0030.pdf
	time ./ExecutePlot --Histogram HDPhiCent3090Subtracted --Output Meow3090.pdf
	cp Meow*.pdf ~/public/html/

ExecutePlot: EEMM.cpp
	CompileRootMacro EEMM.cpp ExecutePlot

Execute: BasicPlots.cpp
	CompileRootMacro BasicPlots.cpp Execute
