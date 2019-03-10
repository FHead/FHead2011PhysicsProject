export DYLD_LIBRARY_PATH=$(shell root-config --libdir)

Jewel = Plots_Off_S_N.root Plots_Off_SB_N.root Plots_On_S_Y.root Plots_On_SB_Y.root Plots_Vac_S_N.root Plots_Vac_SB_N.root
QPythia = Plots_Q1_S.root Plots_QV_S.root Plots_Q1_SB.root Plots_QV_SB.root

default: Execute

RunJetRAAPlots: MakeJetRAAPlots.cpp
	CompileRootMacro MakeJetRAAPlots.cpp RunJetRAAPlots
	
RunBeautifulJetRAAPlots: MakePlot.cpp
	CompileRootMacro MakePlot.cpp RunBeautifulJetRAAPlots

Execute: RunJetRAAPlots RunBeautifulJetRAAPlots $(Jewel) $(QPythia)
	mkdir -p Plots
	./RunBeautifulJetRAAPlots

Plots_Off_S_N.root: RunJetRAAPlots
	./RunJetRAAPlots 16574LargeJewelSamplesMerged/Result_RecoilOff_S.root Plots_Off_S_N N

Plots_Off_SB_N.root: RunJetRAAPlots
	./RunJetRAAPlots 16574LargeJewelSamplesMerged/Result_RecoilOff_SB.root Plots_Off_SB_N N

Plots_On_S_Y.root: RunJetRAAPlots
	./RunJetRAAPlots 16574LargeJewelSamplesMerged/Result_RecoilOn_S.root Plots_On_S_Y Y

Plots_On_SB_Y.root: RunJetRAAPlots
	./RunJetRAAPlots 16574LargeJewelSamplesMerged/Result_RecoilOn_SB.root Plots_On_SB_Y Y

Plots_Vac_S_N.root: RunJetRAAPlots
	./RunJetRAAPlots 16574LargeJewelSamplesMerged/Result_Vac_S.root Plots_Vac_S_N N

Plots_Vac_SB_N.root: RunJetRAAPlots
	./RunJetRAAPlots 16574LargeJewelSamplesMerged/Result_Vac_SB.root Plots_Vac_SB_N N

Plots_Q1_SB.root: RunJetRAAPlots
	./RunJetRAAPlots 16666Samples/Result_QPythia_SB_qhat1.root Plots_Q1_SB N

Plots_QV_SB.root: RunJetRAAPlots
	./RunJetRAAPlots 16666Samples/Result_QPythia_SB_vac.root Plots_QV_SB N

Plots_Q1_S.root: RunJetRAAPlots
	./RunJetRAAPlots 16666Samples/Result_QPythia_S_qhat1.root Plots_Q1_S N

Plots_QV_S.root: RunJetRAAPlots
	./RunJetRAAPlots 16666Samples/Result_QPythia_S_vac.root Plots_QV_S N

Plots_Q1_SB_Merged.root: RunJetRAAPlots
	./RunJetRAAPlots 16666Samples/Result_QPythia_SB_qhat1_Merged.root Plots_Q1_SB_Merged N

Plots_QV_SB_Merged.root: RunJetRAAPlots
	./RunJetRAAPlots 16666Samples/Result_QPythia_SB_vac_Merged.root Plots_QV_SB_Merged N

Plots_Q1_S_Merged.root: RunJetRAAPlots
	./RunJetRAAPlots 16666Samples/Result_QPythia_S_qhat1_Merged.root Plots_Q1_S_Merged N

Plots_QV_S_Merged.root: RunJetRAAPlots
	./RunJetRAAPlots 16666Samples/Result_QPythia_S_vac_Merged.root Plots_QV_S_Merged N


