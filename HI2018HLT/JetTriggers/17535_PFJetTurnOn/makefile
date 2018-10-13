default: RunTTbar

Execute: PlotTurnOn.cpp
	CompileRootMacro PlotTurnOn.cpp Execute -I../../CommonCode/include ../../CommonCode/library/*.o

RunMakePlot: MakeFinalPlots.cpp
	CompileRootMacro MakeFinalPlots.cpp RunMakePlot

RunTTbar: RunTTbarPart1 RunTTbarPart2
	cp TurnOns*.pdf ~/public/html/

RunTTbarPart1: Execute
	./Execute --Input Forest/HiForestAOD_ttbar_2017beamspot.root --HLT openHLT_new.root \
		--Output TurnOnCurvesWithCS.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1,HLT_PuAK4PFJet80Eta5p1_v1,HLT_PuAK4PFJet100Eta5p1_v1,HLT_CsAK4PFJet80Eta2p4_v1
	./Execute --Input Forest/HiForestAOD_ttbar_2017beamspot.root --HLT openHLT_new.root \
		--Output TurnOnCurvesWithPU.root \
		--Jet "akPu4PFJetAnalyzer/t" \
		--Trigger HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1,HLT_PuAK4PFJet80Eta5p1_v1,HLT_PuAK4PFJet100Eta5p1_v1,HLT_CsAK4PFJet80Eta2p4_v1

RunTTbarPart2: RunMakePlot
	./RunMakePlot --Input TurnOnCurvesWithPU.root --Output TurnOnsPU.pdf \
		--Trigger HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4PFJet80Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4PFJet100Eta5p1_v1,HLT_CsAK4PFJet80Eta2p4_v1
	./RunMakePlot --Input TurnOnCurvesWithCS.root --Output TurnOnsCS.pdf \
		--Trigger HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4PFJet80Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4PFJet100Eta5p1_v1,HLT_CsAK4PFJet80Eta2p4_v1

