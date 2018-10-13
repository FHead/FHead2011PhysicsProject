InputForestDiJet80     = Forest103X/HiForestAOD_dijet80_200k.root
InputHLTDiJet80        = openHLT_DiJet80.root

TriggerListFull        = HLT_HIPuAK4CaloJet40Eta5p1_v1,HLT_HIPuAK4CaloJet80Eta5p1_v1
TriggerListForward     = HLT_HIPuAK4CaloJet80Fwd_v1
TriggerListCentral     = HLT_HIPuAK4CaloJet40Eta5p1_v1
TriggerListVeryCentral = HLT_HICsAK4PFJet80Eta1p5_v1,HLT_HIPuAK4CaloJet40Eta5p1_v1,HLT_HIPuAK4CaloJet80Eta5p1_v1

TriggerFull            = HLT_HIPuAK4CaloJet40Eta5p1_v1,HLT_HIPuAK4CaloJet50Eta5p1_v1,HLT_HIPuAK4CaloJet60Eta5p1_v1,HLT_HIPuAK4CaloJet70Eta5p1_v1,HLT_HIPuAK4CaloJet80Eta5p1_v1,HLT_HIPuAK4CaloJet90Eta5p1_v1,HLT_HIPuAK4CaloJet100Eta5p1_v1,HLT_HIPuAK4CaloJet110Eta5p1_v1,HLT_HIPuAK4CaloJet120Eta5p1_v1
LabelFull              = "40","50","60","70","80","90","100","110","120"
TriggerFullFrom60      = HLT_HIPuAK4CaloJet60Eta5p1_v1,HLT_HIPuAK4CaloJet70Eta5p1_v1,HLT_HIPuAK4CaloJet80Eta5p1_v1,HLT_HIPuAK4CaloJet90Eta5p1_v1,HLT_HIPuAK4CaloJet100Eta5p1_v1,HLT_HIPuAK4CaloJet110Eta5p1_v1,HLT_HIPuAK4CaloJet120Eta5p1_v1
LabelFullFrom60        = "60","70","80","90","100","110","120"
TriggerForward         = HLT_HIPuAK4CaloJet40Fwd_v1,HLT_HIPuAK4CaloJet50Fwd_v1,HLT_HIPuAK4CaloJet60Fwd_v1,HLT_HIPuAK4CaloJet70Fwd_v1,HLT_HIPuAK4CaloJet80Fwd_v1,HLT_HIPuAK4CaloJet90Fwd_v1,HLT_HIPuAK4CaloJet100Fwd_v1,HLT_HIPuAK4CaloJet110Fwd_v1,HLT_HIPuAK4CaloJet120Fwd_v1
LabelForward           = "40","50","60","70","80","90","100","110","120"
TriggerCentral         = 
TriggerVeryCentral     = HLT_HICsAK4PFJet60Eta1p5_v1,HLT_HICsAK4PFJet70Eta1p5_v1,HLT_HICsAK4PFJet80Eta1p5_v1,HLT_HICsAK4PFJet90Eta1p5_v1,HLT_HICsAK4PFJet100Eta1p5_v1,HLT_HICsAK4PFJet110Eta1p5_v1,HLT_HICsAK4PFJet120Eta1p5_v1
LabelVeryCentral       = "60","70","80","90","100","110","120"
TriggerList            = HLT_HIPuAK4CaloJet40Eta5p1_v1,HLT_HIPuAK4CaloJet50Eta5p1_v1,HLT_HIPuAK4CaloJet60Eta5p1_v1,HLT_HIPuAK4CaloJet70Eta5p1_v1,HLT_HIPuAK4CaloJet80Eta5p1_v1,HLT_HIPuAK4CaloJet90Eta5p1_v1,HLT_HIPuAK4CaloJet100Eta5p1_v1,HLT_HIPuAK4CaloJet110Eta5p1_v1,HLT_HIPuAK4CaloJet120Eta5p1_v1,HLT_HIPuAK4CaloJet40Fwd_v1,HLT_HIPuAK4CaloJet50Fwd_v1,HLT_HIPuAK4CaloJet60Fwd_v1,HLT_HIPuAK4CaloJet70Fwd_v1,HLT_HIPuAK4CaloJet80Fwd_v1,HLT_HIPuAK4CaloJet90Fwd_v1,HLT_HIPuAK4CaloJet100Fwd_v1,HLT_HIPuAK4CaloJet110Fwd_v1,HLT_HIPuAK4CaloJet120Fwd_v1,HLT_HICsAK4PFJet60Eta1p5_v1,HLT_HICsAK4PFJet70Eta1p5_v1,HLT_HICsAK4PFJet80Eta1p5_v1,HLT_HICsAK4PFJet90Eta1p5_v1,HLT_HICsAK4PFJet100Eta1p5_v1,HLT_HICsAK4PFJet110Eta1p5_v1,HLT_HICsAK4PFJet120Eta1p5_v1

default: RunTTbar RunDiJet80 RunDiJet100 RunCombined

Execute: PlotTurnOn.cpp
	CompileRootMacro PlotTurnOn.cpp Execute -I../../CommonCode/include ../../CommonCode/library/*.o

RunMakePlot: MakeFinalPlots.cpp
	CompileRootMacro MakeFinalPlots.cpp RunMakePlot

RunMakePrettyPlot: MakePrettyPlots.cpp
	CompileRootMacro MakePrettyPlots.cpp RunMakePrettyPlot

RunDiJet80: RunDiJet80Part1 RunDiJet80Part2
	cp TurnOns*.pdf ~/public/html/

RunDiJet80Part1: Execute
	./Execute --Input $(InputForestDiJet80) --HLT $(InputHLTDiJet80) \
		--Output TurnOnCurvesWithCS_DiJet80.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger $(TriggerList)
	./Execute --Input $(InputForestDiJet80) --HLT $(InputHLTDiJet80) \
		--Output TurnOnCurvesWithPU_DiJet80.root \
		--Jet "akPu4CaloJetAnalyzer/t" \
		--Trigger $(TriggerList)

RunDiJet80Part2: RunMakePlot
	./RunMakePlot --Input TurnOnCurvesWithPU_DiJet80.root --Output TurnOnsPU_DiJet80.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)
	./RunMakePlot --Input TurnOnCurvesWithCS_DiJet80.root --Output TurnOnsCS_DiJet80.pdf \
		--TriggerFull $(TriggerListFull) \
		--TriggerForward $(TriggerListForward) \
		--TriggerCentral $(TriggerListCentral) \
		--TriggerVeryCentral $(TriggerListVeryCentral)

RunDiJet80Part3: RunMakePrettyPlot
	./RunMakePrettyPlot --Input TurnOnCurvesWithCS_DiJet80.root --Output TurnOns_CSPF_CSPF.pdf \
		--Trigger $(TriggerVeryCentral) --Label $(LabelVeryCentral) --Name "HVeryCentralJetPT"
