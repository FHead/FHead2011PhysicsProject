default: RunPercentage

ReadTree.o: ReadTree.cpp
	CompileRootMacro ReadTree.cpp ReadTree.o -c | grep -v warning

JetEnergyScale.o: JetEnergyScale.cpp
	CompileRootMacro JetEnergyScale.cpp JetEnergyScale.o -c | grep -v warning

RunPercentage: MakePercentages.cpp ReadTree.o JetEnergyScale.o
	CompileRootMacro MakePercentages.cpp RunPercentage ReadTree.o JetEnergyScale.o

ExecutePercentage: RunPercentage
	./RunPercentage Y 0 MC
	# ./RunPercentage N NONE Data
	# ./RunPercentage 0 N 100 DataPrescale_100
	# ./RunPercentage 0 N 80 DataPrescale_80
	# ./RunPercentage 0 N 60 DataPrescale_60

RunQuickPlot: MakeQuickPlot.cpp
	CompileRootMacro MakeQuickPlot.cpp RunQuickPlot
	./RunQuickPlot Graphs_MC.root QuickPlot_MC
	# ./RunQuickPlot Graphs_Data.root QuickPlot_Data
	# ./RunQuickPlot Graphs_MCShifted.root QuickPlot_MCShifted

RunCPPlot: MakeCPPlot.cpp
	CompileRootMacro MakeCPPlot.cpp RunCPPlot
	./RunCPPlot Graphs_MC.root CPPlot_MC
	./RunCPPlot Graphs_Data.root CPPlot_Data

