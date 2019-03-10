default: FullRun

Execute: MakeScalingPlot.cpp HelperFunctions.h
	CompileRootMacro MakeScalingPlot.cpp Execute

TestRun: Execute
	./Execute --input TestRunHistograms.root --output TestRunScalingPlots.pdf --curves TestRunScalingCurves.root

FullRun: Execute
	./Execute --input TTbar.root --output ScalingPlots.pdf --curves ScalingCurves.root
