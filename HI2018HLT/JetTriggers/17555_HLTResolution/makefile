InputForest = Forest/HiForestAOD_ttbar_2017beamspot_ForestV2.root
InputForest = /tmp/chenyi/HiForestAOD_ttbar_2017beamspot_ForestV2.root
InputHLT    = openHLT.root
TriggerList = HLT_PuAK4CaloJet50Eta5p1_v1,HLT_CsAK4PFJet80Eta2p4_v1,HLT_CsAK4PFJet60Eta1p5_v1

default: TestRunPart1 TestRunPart2

TestRunPart1: Execute
	./Execute --Input $(InputForest) --HLT $(InputHLT) \
		--Output ResolutionPlotsPU.root \
		--Jet "akPu4CaloJetAnalyzer/t" \
		--Trigger $(TriggerList)
	./Execute --Input $(InputForest) --HLT $(InputHLT) \
		--Output ResolutionPlotsCS.root \
		--Jet "akCs4PFJetAnalyzer/t" \
		--Trigger $(TriggerList)
	
TestRunPart2: ExecutePlots
	./ExecutePlots --Input ResolutionPlotsPU.root --Output PlotsPU.pdf \
		--Trigger $(TriggerList)
	./ExecutePlots --Input ResolutionPlotsCS.root --Output PlotsCS.pdf \
		--Trigger $(TriggerList)
	cp Plots*pdf ~/public/html

Execute: MakeResolutionPlots.cpp
	CompileRootMacro MakeResolutionPlots.cpp Execute -I../../CommonCode/include ../../CommonCode/library/*.o

ExecutePlots: MakeFinalPlots.cpp
	CompileRootMacro MakeFinalPlots.cpp ExecutePlots


