default: FullRun

Execute: MakeScalingPlot.cpp HelperFunctions.h
	CompileRootMacro MakeScalingPlot.cpp Execute

TestRun: Execute
	./Execute --input TestRunHistograms.root --output TestRunScalingPlots.pdf --curves TestRunScalingCurves.root
	cp TestRunScalingPlots.pdf ~/public/html/

FullRun: FullRunTTbarJets FullRunTTbarHT FullRunWLNu FullRunHGG FullRunVBFHInv

FullRunTTbarJets: Execute
	./Execute --input TTbar.root --output ScalingPlotsTTbarJets.pdf \
		--curves ScalingCurvesTTbarJets.root \
		--DoJet true --DoMu false --DoE false --DoG false --DoHT false
	mv ScalingCurves.root ScalingCurvesTTbarJets.root
	cp ScalingPlots*.pdf ~/public/html/

FullRunTTbarHT: Execute
	./Execute --input TTbar.root --output ScalingPlotsTTbarHT.pdf \
		--curves ScalingCurvesTTbarHT.root \
		--DoJet false --DoMu false --DoE false --DoG false --DoHT true
	mv ScalingCurves.root ScalingCurvesTTbarHT.root
	cp ScalingPlots*.pdf ~/public/html/

FullRunWLNu: Execute
	./Execute --input WLNu.root --output ScalingPlotsWLNu.pdf \
		--curves ScalingCurvesWLNu.root \
		--DoJet false --DoMu true --DoE true --DoG false --DoHT false
	mv ScalingCurves.root ScalingCurvesWLNu.root
	cp ScalingPlots*.pdf ~/public/html/

FullRunHGG: Execute
	./Execute --input HGG.root --output ScalingPlotsHGG.pdf \
		--curves ScalingCurvesHGG.root \
		--DoJet false --DoMu false --DoE false --DoG true --DoHT false
	mv ScalingCurves.root ScalingCurvesHGG.root
	cp ScalingPlots*.pdf ~/public/html/

FullRunVBFHInv: Execute
	./Execute --input VBFHInv.root --output ScalingPlotsVBFHInv.pdf \
		--curves ScalingCurvesVBFHInv.root \
		--DoJet false --DoMu false --DoE false --DoG false --DoHT true
	mv ScalingCurves.root ScalingCurvesVBFHInv.root
	cp ScalingPlots*.pdf ~/public/html/


