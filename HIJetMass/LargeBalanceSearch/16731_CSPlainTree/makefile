# FASTJET     = /cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
# FASTCONTRIB = /cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet-contrib/1.014/
FASTJET     = /afs/cern.ch/user/c/chenyi/work/Programs/fastjet/install/bin/
FASTCONTRIB = /afs/cern.ch/user/c/chenyi/work/Programs/fastjet/install

.PHONY: ExecutePercentagePlot

default: Run RunPercentagePlot ExecutePercentagePlot

Run: MakePlainTree.cpp
	CompileRootMacro MakePlainTree.cpp Run \
		-I../../CommonCode/include ../../CommonCode/library/*o \
		`$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs` \
		-I$(FASTCONTRIB)/include $(FASTCONTRIB)/lib/*.a

RunPercentagePlot: MakePercentagePlot.cpp
	CompileRootMacro MakePercentagePlot.cpp RunPercentagePlot

ExecutePercentagePlot: RunPercentagePlot
	./RunPercentagePlot ScaledResult/PP6Dijet.root PP6 NONE -1 -1 "PP6Dijet"
	# ./RunPercentagePlot ScaledResult/AA6Dijet.root AA6 NONE -1 -1 "AA6DijetDrum"
	# ./RunPercentagePlot ScaledResult/AA6Dijet.root AA6C0 NONE 0.0 0.1 "AA6DijetDrumC0"
	# ./RunPercentagePlot ScaledResult/AA6Dijet.root AA6C1 NONE 0.1 0.3 "AA6DijetDrumC1"
	# ./RunPercentagePlot ScaledResult/AA6Dijet.root AA6C2 NONE 0.3 0.5 "AA6DijetDrumC2"
	# ./RunPercentagePlot ScaledResult/AA6Dijet.root AA6C3 NONE 0.5 0.8 "AA6DijetDrumC3"
	./RunPercentagePlot ScaledResult/AAData.root AAData PbPb100 -1 -1 "AAData"
	./RunPercentagePlot ScaledResult/AAData.root AADataC0 PbPb100 0.0 0.1 "AADataC0"
	./RunPercentagePlot ScaledResult/AAData.root AADataC1 PbPb100 0.1 0.3 "AADataC1"
	./RunPercentagePlot ScaledResult/AAData.root AADataC2 PbPb100 0.3 0.5 "AADataC2"
	./RunPercentagePlot ScaledResult/AAData.root AADataC3 PbPb100 0.5 0.8 "AADataC3"
	# ./RunPercentagePlot ScaledResult/PPDataHighPTJet.root PPData NONE -1 -1 "PPData"
	./RunPercentagePlot ScaledResult/AA6DijetCymbalV2.root AA6Cymbal NONE -1 -1 "AA6Dijet"
	./RunPercentagePlot ScaledResult/AA6DijetCymbalV2.root AA6CymbalC0 NONE 0.0 0.1 "AA6DijetC0"
	./RunPercentagePlot ScaledResult/AA6DijetCymbalV2.root AA6CymbalC1 NONE 0.1 0.3 "AA6DijetC1"
	./RunPercentagePlot ScaledResult/AA6DijetCymbalV2.root AA6CymbalC2 NONE 0.3 0.5 "AA6DijetC2"
	./RunPercentagePlot ScaledResult/AA6DijetCymbalV2.root AA6CymbalC3 NONE 0.5 0.8 "AA6DijetC3"

TestRun: Run
	./Run /eos/cms/store/group/phys_heavyions/mverweij/MCPbPb/CymbalDijetPythia6/Pythia6_Dijet220_pp502_Hydjet_Cymbal_MB/crab_HiForestCymbalDijet220P6V2/170630_123929/Merged/Merged_0003_34.root Meow.root AA6Dijet220CymbalV2 -100000 1000000
