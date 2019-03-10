default: TestRun

TestRun: Execute
	./Execute
	cp *pdf ~/public/html

Execute: PlotL2Res.cpp
	CompileRootMacro PlotL2Res.cpp Execute
