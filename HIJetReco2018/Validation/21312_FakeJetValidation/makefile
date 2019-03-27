FASTJET = /cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/

default: DebugRun

Execute: MakeBasicPlots.cpp
	CompileRootMacro MakeBasicPlots.cpp Execute \
		`$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs` \
		-I../../CommonCode/include ../../CommonCode/library/*o

ExecutePlots: MakeComparisonPlots.cpp
	CompileRootMacro MakeComparisonPlots.cpp ExecutePlots

DebugRun: Execute ExecutePlots
	./Execute --Input RelVal_QCD_10_3_2.root --Output Plots_QCD_10_3_2.root --Tree "ak4PFJetAnalyzer/t"
	./Execute --Input RelVal_QCD_10_3_3.root --Output Plots_QCD_10_3_3.root --Tree "ak4PFJetAnalyzer/t"
	./ExecutePlots --InputTarget Plots_QCD_10_3_3.root --InputReference Plots_QCD_10_3_2.root \
		--Output QCD.pdf
	cp QCD.pdf ~/public/html

RunAll: Execute
	./Execute --Input RelVal_PhotonJet_10_3_2.root --Output Plots_PhotonJet_10_3_2.root
	./Execute --Input RelVal_QCD_10_3_2.root --Output Plots_QCD_10_3_2.root
	./Execute --Input RelVal_ZEEMM_10_3_2.root --Output Plots_ZEEMM_10_3_2.root
	./Execute --Input RelVal_PhotonJet_10_3_3.root --Output Plots_PhotonJet_10_3_3.root




