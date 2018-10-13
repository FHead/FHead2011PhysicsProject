InputForest = Forest/HiForestAOD_ttbar_2017beamspot_ForestV2.root
InputHLT    = openHLT.root
TriggerList = HLT_PuAK4CaloJet40Eta5p1_v1,HLT_PuAK4CaloJet50Eta5p1_v1,HLT_PuAK4CaloJet60Eta5p1_v1,HLT_PuAK4CaloJet70Eta5p1_v1,HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet90Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet110Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1,HLT_PuAK4CaloJet40Fwd_v1,HLT_PuAK4CaloJet50Fwd_v1,HLT_PuAK4CaloJet60Fwd_v1,HLT_PuAK4CaloJet70Fwd_v1,HLT_PuAK4CaloJet80Fwd_v1,HLT_PuAK4CaloJet90Fwd_v1,HLT_PuAK4CaloJet100Fwd_v1,HLT_PuAK4CaloJet110Fwd_v1,HLT_PuAK4CaloJet120Fwd_v1,HLT_CsAK4PFJet80Eta2p4_v1,HLT_CsAK4PFJet90Eta2p4_v1,HLT_CsAK4PFJet100Eta2p4_v1,HLT_CsAK4PFJet110Eta2p4_v1,HLT_CsAK4PFJet120Eta2p4_v1,HLT_CsAK4PFJet60Eta1p5_v1,HLT_CsAK4PFJet70Eta1p5_v1,HLT_CsAK4PFJet80Eta1p5_v1,HLT_CsAK4PFJet90Eta1p5_v1,HLT_CsAK4PFJet100Eta1p5_v1,HLT_CsAK4PFJet110Eta1p5_v1,HLT_CsAK4PFJet120Eta1p5_v1

default: RunTTbar

Execute: PlotTurnOn.cpp
	CompileRootMacro PlotTurnOn.cpp Execute -I../../CommonCode/include ../../CommonCode/library/*.o

RunMakePlot: MakeFinalPlots.cpp
	CompileRootMacro MakeFinalPlots.cpp RunMakePlot

RunTTbar: RunTTbarPart1 RunTTbarPart2
	cp TurnOns*.pdf ~/public/html/

RunTTbarPart1: Execute
	./Execute --Input $(InputForest) --HLT $(InputHLT) \
		--Output TurnOnCurvesWithCS.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger $(TriggerList)
	./Execute --Input $(InputForest) --HLT $(InputHLT) \
		--Output TurnOnCurvesWithPU.root \
		--Jet "akPu4CaloJetAnalyzer/t" \
		--Trigger $(TriggerList)

RunTTbarPart2: RunMakePlot
	./RunMakePlot --Input TurnOnCurvesWithPU.root --Output TurnOnsPU.pdf \
		--Trigger $(TriggerList)
	./RunMakePlot --Input TurnOnCurvesWithCS.root --Output TurnOnsCS.pdf \
		--Trigger $(TriggerList)

