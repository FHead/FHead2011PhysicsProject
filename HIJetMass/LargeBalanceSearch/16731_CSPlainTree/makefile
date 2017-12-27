FASTJET     = /cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
FASTCONTRIB = /cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet-contrib/1.014/

default: Run RunPercentagePlot ExecutePercentagePlot

Run: MakePlainTree.cpp
	CompileRootMacro MakePlainTree.cpp Run \
		-I../../CommonCode/include ../../CommonCode/library/*o \
		`$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs` \
		-I$(FASTCONTRIB)/include $(FASTCONTRIB)/lib/*.a

RunPercentagePlot: MakePercentagePlot.cpp
	CompileRootMacro MakePercentagePlot.cpp RunPercentagePlot
	./RunPercentagePlot ScaledResult/PP6Dijet.root PP6 NONE -1 -1
	./RunPercentagePlot ScaledResult/AA6Dijet.root AA6 NONE -1 -1
	./RunPercentagePlot ScaledResult/AA6Dijet.root AA6C0 NONE 0.0 0.1
	./RunPercentagePlot ScaledResult/AA6Dijet.root AA6C1 NONE 0.1 0.3
	./RunPercentagePlot ScaledResult/AA6Dijet.root AA6C2 NONE 0.3 0.5
	./RunPercentagePlot ScaledResult/AA6Dijet.root AA6C3 NONE 0.5 0.8
	./RunPercentagePlot ScaledResult/AAData.root AAData PbPb100 -1 -1
	./RunPercentagePlot ScaledResult/AAData.root AADataC0 PbPb100 0.0 0.1
	./RunPercentagePlot ScaledResult/AAData.root AADataC1 PbPb100 0.1 0.3
	./RunPercentagePlot ScaledResult/AAData.root AADataC2 PbPb100 0.3 0.5
	./RunPercentagePlot ScaledResult/AAData.root AADataC3 PbPb100 0.5 0.8

ExecutePercentagePlot: RunPercentagePlot


