default: FullRunJetOnly

Execute: MakeScalingPlot.cpp HelperFunctions.h
	CompileRootMacro MakeScalingPlot.cpp Execute

TestRun: Execute
	./Execute --input TestRunHistograms.root --output TestRunScalingPlots.pdf --curves TestRunScalingCurves.root
	cp TestRunScalingPlots.pdf ~/public/html/

FullRun: Execute
	./Execute --input TTbar.root --output ScalingPlots.pdf --curves ScalingCurves.root
	cp ScalingPlots.pdf ~/public/html/

FullRunJetOnly: Execute
	./Execute --input TTbar.root --output ScalingPlots.pdf --curves ScalingCurves.root \
		--dojet true --domuon false --doeg false --doht false
	cp ScalingPlots.pdf ~/public/html/
