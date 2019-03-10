default: TestRun

Execute: PlotOccupancy.cpp
	CompileRootMacro PlotOccupancy.cpp Execute

TestRun: Execute
	./Execute --input SampleBase/0000/JRA_999.root --output TestRun.root

FullRun: Execute
	mkdir -p Result
	rm -f Result/*root
	for i in SampleBase/*/*root; do echo $$i; ./Execute --input $$i --output Result/`basename $$i`; done

RunMakePlot: MakeFinalPlot.cpp
	CompileRootMacro MakeFinalPlot.cpp RunMakePlot
	
ExecutePlot: RunMakePlot
	hadd -k -f All.root Result/*root
	./RunMakePlot --input All.root
	cp Meow[12].pdf ~/public/html/
