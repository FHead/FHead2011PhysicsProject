default: FullRunEGOnly

Execute: MakeScalingPlot.cpp HelperFunctions.h
	CompileRootMacro MakeScalingPlot.cpp Execute

TestRun: Execute
	./Execute --input TestRunHistograms.root --output TestRunScalingPlots.pdf --curves TestRunScalingCurves.root
	cp TestRunScalingPlots.pdf ~/public/html/

FullRun: Execute
	./Execute --input TTbar.root --output ScalingPlots1.pdf \
		--curves ScalingCurves1.root \
		--dojet true --domuon false --doeg false --doht false
	./Execute --input TTbar.root --output ScalingPlots2.pdf \
		--curves ScalingCurves2.root \
		--dojet false --domuon true --doeg false --doht false
	./Execute --input TTbar.root --output ScalingPlots3.pdf \
		--curves ScalingCurves3.root \
		--dojet false --domuon false --doeg true --doht false
	./Execute --input TTbar.root --output ScalingPlots4.pdf \
		--curves ScalingCurves4.root \
		--dojet false --domuon false --doeg false --doht true
	cp ScalingPlots*.pdf ~/public/html/

FullRunJetOnly: Execute
	./Execute --input TTbar.root --output ScalingPlots.pdf --curves ScalingCurves.root \
		--dojet true --domuon false --doeg false --doht false
	cp ScalingPlots.pdf ~/public/html/

FullRunEGOnly: Execute
	./Execute --input TTbar.root --output ScalingPlots.pdf --curves ScalingCurves.root \
		--dojet false --domuon false --doeg true --doht false
	cp ScalingPlots.pdf ~/public/html/
