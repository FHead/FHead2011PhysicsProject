FASTJET = /cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/

default: RunTest

RunTest: Execute ExecutePlot
	./Execute --Input Output/Result_53.root --Output TestRun.root
	./ExecutePlot --Input TestRun.root --Output TestRun.pdf
	cp TestRun.pdf ~/public/html/

RunRnD: Execute ExecutePlot
	./Execute --Input RnD.root --Output RnDPlots.root
	./ExecutePlot --Input RnDPlots.root --Output RnDPlots.pdf
	cp RnDPlots.pdf ~/public/html/

RunAll: Execute ExecutePlot
	./Execute --Input `ls Output/* | head -n 100 | tr '\n' ','` --Output AllRun.root
	./ExecutePlot --Input AllRun.root --Output AllPlots.pdf
	cp AllPlots.pdf ~/public/html/

Execute: QuickLook.cpp
	CompileRootMacro QuickLook.cpp Execute \
		`$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs` \
		-I../../CommonCode/include ../../CommonCode/library/*o

ExecutePlot: MakePlot.cpp
	CompileRootMacro MakePlot.cpp ExecutePlot

