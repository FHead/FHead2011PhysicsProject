export LD_LIBRARY_PATH = /Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros

default: TestRun

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute

TestRun: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros \
		./Execute --input Sample1.root --output PlotsSample1PF_Resolution.pdf --algorithm ak4pf \
		   --doresponse true --dostack false --dofraction false --doresolution true
