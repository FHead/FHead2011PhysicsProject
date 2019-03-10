default: TestRun

Execute: PlotImage.cpp
	CompileRootMacro PlotImage.cpp Execute

TestRun: Execute
	./Execute --input Input/JetTree_0.root --output TestRun.pdf --fraction 1.0 --minjetpt 270 --max 250
