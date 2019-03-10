default: TestRunGroom

Execute: PlotSlice.cpp
	CompileRootMacro PlotSlice.cpp Execute

ExecuteGroom: PlotUsual.cpp
	CompileRootMacro PlotUsual.cpp ExecuteGroom

TestRun: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros ./Execute
	convert LundPlane.pdf -trim +repage LundPlane.png

TestRunGroom: ExecuteGroom
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros ./ExecuteGroom

