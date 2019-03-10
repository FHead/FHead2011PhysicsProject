# FASTJET     = /cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
FASTJET     = /afs/cern.ch/user/c/chenyi/work/Programs/fastjet/install/bin/
FASTCONTRIB = /afs/cern.ch/user/c/chenyi/work/Programs/fastjet/install

default: RunSmear RunPercentagePlot RunQuickPlot

RunSmear: JetMassPlots.cpp
	CompileRootMacro JetMassPlots.cpp RunSmear \
	   -I../../CommonCode/include ../../CommonCode/library/* \
	   `$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs` \
	   -I$(FASTCONTRIB)/include $(FASTCONTRIB)/lib/*.a

RunPercentagePlot: MakePercentagePlot.cpp
	CompileRootMacro MakePercentagePlot.cpp RunPercentagePlot
	./RunPercentagePlot ScaledResult/PP6Dijet.root PP6Mixed NONE -1 -1 PP6DijetMixed
	./RunPercentagePlot ScaledResult/PP6Dijet.root PP6MixedC0 NONE 0.0 0.1 PP6DijetMixedC0
	./RunPercentagePlot ScaledResult/PP6Dijet.root PP6MixedC1 NONE 0.1 0.3 PP6DijetMixedC1
	./RunPercentagePlot ScaledResult/PP6Dijet.root PP6MixedC2 NONE 0.3 0.5 PP6DijetMixedC2
	./RunPercentagePlot ScaledResult/PP6Dijet.root PP6MixedC3 NONE 0.5 0.8 PP6DijetMixedC3
	# ./RunPercentagePlot ScaledResult/PPDataHighPTJet.root PPDataMixed NONE -1 -1 PPDataMixed
	# ./RunPercentagePlot ScaledResult/PPDataHighPTJet.root PPDataMixedC0 NONE 0.0 0.1 PPDataMixedC0
	# ./RunPercentagePlot ScaledResult/PPDataHighPTJet.root PPDataMixedC1 NONE 0.1 0.3 PPDataMixedC1
	# ./RunPercentagePlot ScaledResult/PPDataHighPTJet.root PPDataMixedC2 NONE 0.3 0.5 PPDataMixedC2
	# ./RunPercentagePlot ScaledResult/PPDataHighPTJet.root PPDataMixedC3 NONE 0.5 0.8 PPDataMixedC3

RunQuickPlot: MakeQuickPlot.cpp
	CompileRootMacro MakeQuickPlot.cpp RunQuickPlot
	./RunQuickPlot
