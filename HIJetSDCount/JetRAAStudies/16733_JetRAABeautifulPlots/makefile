export DYLD_LIBRARY_PATH=$(shell root-config --libdir)

default: Execute

RunJetRAAPlots: MakeJetRAAPlots.cpp
	CompileRootMacro MakeJetRAAPlots.cpp RunJetRAAPlots
	
RunBeautifulJetRAAPlots: MakePlot.cpp
	CompileRootMacro MakePlot.cpp RunBeautifulJetRAAPlots

Execute: RunJetRAAPlots RunBeautifulJetRAAPlots
	./RunJetRAAPlots 16541Samples/Result_RecoilOff_S.root Plots_Off_S_N N
	./RunJetRAAPlots 16541Samples/Result_RecoilOff_SB.root Plots_Off_SB_N N
	./RunJetRAAPlots 16541Samples/Result_RecoilOff_P.root Plots_Off_P_N N
	./RunJetRAAPlots 16541Samples/Result_RecoilOn_S.root Plots_On_S_Y Y
	./RunJetRAAPlots 16541Samples/Result_RecoilOn_SB.root Plots_On_SB_Y Y
	./RunJetRAAPlots 16541Samples/Result_RecoilOn_P.root Plots_On_P_Y Y
	./RunBeautifulJetRAAPlots
