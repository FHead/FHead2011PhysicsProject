default: RunTTbar

Execute: PlotTurnOn.cpp
	CompileRootMacro PlotTurnOn.cpp Execute -I../../CommonCode/include ../../CommonCode/library/*.o

RunMakePlot: MakeFinalPlots.cpp
	CompileRootMacro MakeFinalPlots.cpp RunMakePlot

RunTTbar: RunTTbarPart1 RunTTbarPart2

RunTTbarPart1: Execute
	./Execute --Input Forest/HiForestAOD_ttbar_10k.root --HLT openHLT10000.root \
		--Output TurnOnCurves.root \
		--Jet "akPu4PFJetAnalyzer/t" \
		--Trigger HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1

RunTTbarPart2: RunMakePlot
	./RunMakePlot --Input TurnOnCurves.root --Output TurnOns.pdf \
		--Trigger HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1

