default: PlotRun

TestRun: Execute
	./Execute --input SamplesHHbbTauTau/L1NtuplePhaseII_MTD_1.root \
		--output Tree.root

FullRun: Execute
	./Execute --input `ls SamplesHHbbTauTau/* | tr '\n' ',' | sed "s/,$$//g"` \
		--output FullTree.root

PlotRun: MakePlot.cpp
	CompileRootMacro MakePlot.cpp ExecutePlot
	./ExecutePlot
	cp Meow.pdf ~/public/html

Execute: FillTree.cpp
	CompileRootMacro FillTree.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o
