CompileRootMacro ReadTree.cpp ReadTree.o -c | grep -v warning
CompileRootMacro JetEnergyScale.cpp JetEnergyScale.o -c | grep -v warning
CompileRootMacro EstimateSystematics.cpp RunSystematics ReadTree.o JetEnergyScale.o
CompileRootMacro CombineSystematics.cpp RunCombination
