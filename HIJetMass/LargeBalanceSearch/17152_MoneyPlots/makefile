default: RunPercentage

ReadTree.o: ReadTree.cpp
	CompileRootMacro ReadTree.cpp ReadTree.o -c | grep -v warning

JetEnergyScale.o: JetEnergyScale.cpp
	CompileRootMacro JetEnergyScale.cpp JetEnergyScale.o -c | grep -v warning

RunPercentage: MakePercentages.cpp ReadTree.o JetEnergyScale.o
	CompileRootMacro MakePercentages.cpp RunPercentage ReadTree.o JetEnergyScale.o

ExecutePercentage: RunPercentage
	# ./RunPercentage Y 0 MCNominal Default
	# ./RunPercentage Y 0 MCJECUp JECUp
	# ./RunPercentage Y 0 MCJECDown JECDown
	# ./RunPercentage Y 0 MCRJECUp RJECUp
	# ./RunPercentage Y 0 MCRJECDown RJECDown
	# ./RunPercentage Y 0 MCRhoUp RhoUp
	# ./RunPercentage Y 0 MCRhoDown RhoDown
	# ./RunPercentage Y 0 MCPbPbJER PbPbJER
	# ./RunPercentage Y 0 MCPPJER PPJER
	# ./RunPercentage Y 0 MCRhoShift RhoShift
	# ./RunPercentage Y 0 MCDRUp DRUp
	# ./RunPercentage Y 0 MCDRDown DRDown
	# ./RunPercentage Y 0 MCRDRUp RDRUp
	# ./RunPercentage Y 0 MCRDRDown RDRDown
	# ./RunPercentage Y 0 MCShifted Shifted
	# ./RunPercentage Y 0 MCHIReco HIReco
	# ./RunPercentage Y 0 MCPythia8 Pythia8
	# ./RunPercentage Y 0 MCPythia8Large Pythia8Large
	./RunPercentage Y 0 MCCentralFocus CentralFocus
	# ./RunPercentage N NONE Data
	# ./RunPercentage 0 N 100 DataPrescale_100
	# ./RunPercentage 0 N 80 DataPrescale_80
	# ./RunPercentage 0 N 60 DataPrescale_60

RunQuickPlot: MakeQuickPlot.cpp
	CompileRootMacro MakeQuickPlot.cpp RunQuickPlot

RunSummaryPlot: MakeSummaryPlot.cpp
	CompileRootMacro MakeSummaryPlot.cpp RunSummaryPlot

ExecuteSummaryPlot: RunSummaryPlot
	# ./RunSummaryPlot Graphs_MCNominal.root SummaryPlot_MCNominal N
	# ./RunSummaryPlot Graphs_MCNominal.root SummaryPlot_MCNominalCorrected Y
	# ./RunSummaryPlot Graphs_MCJECUp.root SummaryPlot_MCJECUp N
	# ./RunSummaryPlot Graphs_MCJECDown.root SummaryPlot_MCJECDown N
	# ./RunSummaryPlot Graphs_MCRJECUp.root SummaryPlot_MCRJECUp N
	# ./RunSummaryPlot Graphs_MCRJECDown.root SummaryPlot_MCRJECDown N
	# ./RunSummaryPlot Graphs_MCRhoUp.root SummaryPlot_MCRhoUp N
	# ./RunSummaryPlot Graphs_MCRhoDown.root SummaryPlot_MCRhoDown N
	# ./RunSummaryPlot Graphs_MCPbPbJER.root SummaryPlot_MCPbPbJER N
	# ./RunSummaryPlot Graphs_MCPPJER.root SummaryPlot_MCPPJER N
	# ./RunSummaryPlot Graphs_MCRhoShift.root SummaryPlot_MCRhoShift N
	# ./RunSummaryPlot Graphs_MCDRUp.root SummaryPlot_MCDRUp N
	# ./RunSummaryPlot Graphs_MCDRDown.root SummaryPlot_MCDRDown N
	# ./RunSummaryPlot Graphs_MCRDRUp.root SummaryPlot_MCRDRUp N
	# ./RunSummaryPlot Graphs_MCRDRDown.root SummaryPlot_MCRDRDown N
	# ./RunSummaryPlot Graphs_MCShifted.root SummaryPlot_MCShifted N
	# ./RunSummaryPlot Graphs_MCHIReco.root SummaryPlot_MCHIReco N
	# ./RunSummaryPlot Graphs_MCPythia8.root SummaryPlot_MCPythia8 N
	# ./RunSummaryPlot Graphs_MCPythia8Large.root SummaryPlot_MCPythia8Large N
	./RunSummaryPlot Graphs_MCCentralFocus.root SummaryPlot_MCCentralFocus N CentralFocus

RunDerivation: MakeDerivation.cpp
	CompileRootMacro MakeDerivation.cpp RunDerivation
	./RunDerivation | grep ^[0-4] | TextToTree Derivation.root 6 "C:PT:T1:V1:T2:V2"

RunCPPlot: MakeCPPlot.cpp
	CompileRootMacro MakeCPPlot.cpp RunCPPlot
	./RunCPPlot Graphs_MC.root CPPlot_MC
	./RunCPPlot Graphs_Data.root CPPlot_Data

