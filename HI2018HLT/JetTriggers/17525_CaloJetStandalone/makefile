Forest = /eos/cms/store/group/phys_heavyions/ikucher/mc_private_hlt2018/forest_102X//HiForestAOD_ttbar_10k.root
OpenHLT = ../17523_CaloJetTurnOn/openHLT10000.root

default: RunTTbar

Execute: PlotTurnOn.cpp Messenger.h Messenger.cpp
	g++ `root-config --cflags` Messenger.cpp -c -o Messenger.o
	g++ `root-config --libs --cflags` PlotTurnOn.cpp -o Execute Messenger.o

RunMakePlot: MakeFinalPlots.cpp
	g++ `root-config --libs --cflags` MakeFinalPlots.cpp -o RunMakePlot

RunTTbar: RunTTbarPart1 RunTTbarPart2

RunTTbarPart1: Execute
	./Execute --Input $(Forest) --HLT $(OpenHLT) \
		--Output TurnOnCurves.root \
		--Jet "akPu4PFJetAnalyzer/t" \
		--Trigger HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1

RunTTbarPart2: RunMakePlot
	./RunMakePlot --Input TurnOnCurves.root --Output TurnOns.pdf \
		--Trigger HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1

