InputForestTTbar    = Forest/HiForestAOD_ttbar_2017beamspot_ForestV2.root
InputHLTTTbar       = openHLT_TTbar.root
InputForestDiJet60  = Forest/HiForestAOD_diJet60_2017beamspot_ForestV2.root
InputHLTDiJet60     = openHLT_DiJet60.root
InputForestDiJet100 = Forest/HiForestAOD_diJet100_2017beamspot_ForestV2.root
InputHLTDiJet100    = openHLT_DiJet100.root

TriggerListFull        = HLT_PuAK4CaloJet40Eta5p1_v1,HLT_PuAK4CaloJet80Eta5p1_v1
TriggerListForward     = HLT_PuAK4CaloJet80Fwd_v1
TriggerListCentral     = HLT_PuAK4CaloJet40Eta5p1_v1
TriggerListVeryCentral = HLT_CsAK4PFJet80Eta1p5_v1,HLT_PuAK4CaloJet40Eta5p1_v1,HLT_PuAK4CaloJet80Eta5p1_v1

TriggerFull            = HLT_PuAK4CaloJet40Eta5p1_v1,HLT_PuAK4CaloJet50Eta5p1_v1,HLT_PuAK4CaloJet60Eta5p1_v1,HLT_PuAK4CaloJet70Eta5p1_v1,HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet90Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet110Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1
LabelFull              = "40","50","60","70","80","90","100","110","120"
TriggerFullFrom60      = HLT_PuAK4CaloJet60Eta5p1_v1,HLT_PuAK4CaloJet70Eta5p1_v1,HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet90Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet110Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1
LabelFullFrom60        = "60","70","80","90","100","110","120"
TriggerForward         = HLT_PuAK4CaloJet40Fwd_v1,HLT_PuAK4CaloJet50Fwd_v1,HLT_PuAK4CaloJet60Fwd_v1,HLT_PuAK4CaloJet70Fwd_v1,HLT_PuAK4CaloJet80Fwd_v1,HLT_PuAK4CaloJet90Fwd_v1,HLT_PuAK4CaloJet100Fwd_v1,HLT_PuAK4CaloJet110Fwd_v1,HLT_PuAK4CaloJet120Fwd_v1
LabelForward           = "40","50","60","70","80","90","100","110","120"
TriggerCentral         = 
TriggerVeryCentral     = HLT_CsAK4PFJet60Eta1p5_v1,HLT_CsAK4PFJet70Eta1p5_v1,HLT_CsAK4PFJet80Eta1p5_v1,HLT_CsAK4PFJet90Eta1p5_v1,HLT_CsAK4PFJet100Eta1p5_v1,HLT_CsAK4PFJet110Eta1p5_v1,HLT_CsAK4PFJet120Eta1p5_v1
LabelVeryCentral       = "60","70","80","90","100","110","120"
TriggerList            = HLT_PuAK4CaloJet40Eta5p1_v1,HLT_PuAK4CaloJet50Eta5p1_v1,HLT_PuAK4CaloJet60Eta5p1_v1,HLT_PuAK4CaloJet70Eta5p1_v1,HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet90Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet110Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1,HLT_PuAK4CaloJet40Fwd_v1,HLT_PuAK4CaloJet50Fwd_v1,HLT_PuAK4CaloJet60Fwd_v1,HLT_PuAK4CaloJet70Fwd_v1,HLT_PuAK4CaloJet80Fwd_v1,HLT_PuAK4CaloJet90Fwd_v1,HLT_PuAK4CaloJet100Fwd_v1,HLT_PuAK4CaloJet110Fwd_v1,HLT_PuAK4CaloJet120Fwd_v1,HLT_CsAK4PFJet60Eta1p5_v1,HLT_CsAK4PFJet70Eta1p5_v1,HLT_CsAK4PFJet80Eta1p5_v1,HLT_CsAK4PFJet90Eta1p5_v1,HLT_CsAK4PFJet100Eta1p5_v1,HLT_CsAK4PFJet110Eta1p5_v1,HLT_CsAK4PFJet120Eta1p5_v1

default: RunTTbar RunDiJet60 RunDiJet100 RunCombined

Execute: PlotTurnOn.cpp
	CompileRootMacro PlotTurnOn.cpp Execute -I../../CommonCode/include ../../CommonCode/library/*.o

RunMakePlot: MakeFinalPlots.cpp
	CompileRootMacro MakeFinalPlots.cpp RunMakePlot

RunMakePrettyPlot: MakePrettyPlots.cpp
	CompileRootMacro MakePrettyPlots.cpp RunMakePrettyPlot

RunTTbar: RunTTbarPart1 RunTTbarPart2
	cp TurnOns*.pdf ~/public/html/

RunDiJet60: RunDiJet60Part1 RunDiJet60Part2
	cp TurnOns*.pdf ~/public/html/

RunDiJet100: RunDiJet100Part1 RunDiJet100Part2
	cp TurnOns*.pdf ~/public/html/

RunCombined: RunCombinedPart1 RunCombinedPart2 RunCombinedPart3
	cp TurnOns*.pdf ~/public/html/

RunTTbarPart1: Execute
	./Execute --Input $(InputForestTTbar) --HLT $(InputHLTTTbar) \
		--Output TurnOnCurvesWithCS_TTbar.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger $(TriggerList)
	./Execute --Input $(InputForestTTbar) --HLT $(InputHLTTTbar) \
		--Output TurnOnCurvesWithPU_TTbar.root \
		--Jet "akPu4CaloJetAnalyzer/t" \
		--Trigger $(TriggerList)

RunTTbarPart2: RunMakePlot
	./RunMakePlot --Input TurnOnCurvesWithPU_TTbar.root --Output TurnOnsPU_TTbar.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)
	./RunMakePlot --Input TurnOnCurvesWithCS_TTbar.root --Output TurnOnsCS_TTbar.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)

RunDiJet60Part1: Execute
	./Execute --Input $(InputForestDiJet60) --HLT $(InputHLTDiJet60) \
		--Output TurnOnCurvesWithCS_DiJet60.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger $(TriggerList)
	./Execute --Input $(InputForestDiJet60) --HLT $(InputHLTDiJet60) \
		--Output TurnOnCurvesWithPU_DiJet60.root \
		--Jet "akPu4CaloJetAnalyzer/t" \
		--Trigger $(TriggerList)

RunDiJet60Part2: RunMakePlot
	./RunMakePlot --Input TurnOnCurvesWithPU_DiJet60.root --Output TurnOnsPU_DiJet60.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)
	./RunMakePlot --Input TurnOnCurvesWithCS_DiJet60.root --Output TurnOnsCS_DiJet60.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)

RunDiJet100Part1: Execute
	./Execute --Input $(InputForestDiJet100) --HLT $(InputHLTDiJet100) \
		--Output TurnOnCurvesWithCS_DiJet100.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger $(TriggerList)
	./Execute --Input $(InputForestDiJet100) --HLT $(InputHLTDiJet100) \
		--Output TurnOnCurvesWithPU_DiJet100.root \
		--Jet "akPu4CaloJetAnalyzer/t" \
		--Trigger $(TriggerList)

RunDiJet100Part2: RunMakePlot
	./RunMakePlot --Input TurnOnCurvesWithPU_DiJet100.root --Output TurnOnsPU_DiJet100.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)
	./RunMakePlot --Input TurnOnCurvesWithCS_DiJet100.root --Output TurnOnsCS_DiJet100.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)

RunCombinedPart1: RunTTbarPart1 RunDiJet60Part1 RunDiJet100Part1
	hadd -f TurnOnCurvesWithPU.root TurnOnCurvesWithPU_*.root
	hadd -f TurnOnCurvesWithCS.root TurnOnCurvesWithCS_*.root

RunCombinedPart2: RunMakePlot
	./RunMakePlot --Input TurnOnCurvesWithPU.root --Output TurnOnsPU.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)
	./RunMakePlot --Input TurnOnCurvesWithCS.root --Output TurnOnsCS.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)

RunCombinedPart3: RunMakePrettyPlot
	./RunMakePrettyPlot --Input TurnOnCurvesWithPU.root --Output TurnOns_PUCalo_PUCalo.pdf \
		--Trigger $(TriggerFull) \
		--Label $(LabelFull) \
		--Name "HJetPT"
	./RunMakePrettyPlot --Input TurnOnCurvesWithCS.root --Output TurnOns_PUCalo_CSPF.pdf \
		--Trigger $(TriggerFullFrom60) \
		--Label $(LabelFullFrom60) \
		--Name "HVeryCentralJetPT"
	./RunMakePrettyPlot --Input TurnOnCurvesWithPU.root --Output TurnOns_PUCaloFwd_PUCalo.pdf \
		--Trigger $(TriggerForward) \
		--Label $(LabelForward) \
		--Name "HFJetPT"
	./RunMakePrettyPlot --Input TurnOnCurvesWithCS.root --Output TurnOns_CSPF_CSPF.pdf \
		--Trigger $(TriggerVeryCentral) \
		--Label $(LabelVeryCentral) \
		--Name "HVeryCentralJetPT"
	cp TurnOns*pdf ~/public/html/

RunListCSFail: Execute
	./Execute --Input $(InputForestTTbar) --HLT $(InputHLTTTbar) --PrintDrop true \
		--Output Dummy.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger HLT_CsAK4PFJet100Eta1p5_v1 | tee TTbarFail
	./Execute --Input $(InputForestDiJet100) --HLT $(InputHLTDiJet100) --PrintDrop true \
		--Output Dummy.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger HLT_CsAK4PFJet100Eta1p5_v1 | tee DiJet100Fail
	./Execute --Input $(InputForestDiJet60) --HLT $(InputHLTDiJet60) --PrintDrop true \
		--Output Dummy.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger HLT_CsAK4PFJet100Eta1p5_v1 | tee DiJet60Fail
