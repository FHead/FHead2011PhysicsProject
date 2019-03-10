default: RunTest

Execute: PlotJEC.cpp
	CompileRootMacro PlotJEC.cpp Execute

RunTest: TestUncertainty.cpp
	CompileRootMacro TestUncertainty.cpp RunTest
	./RunTest

RunPlot: Execute
	./Execute
	cp JECL2L3Res.pdf ~/public/html/


