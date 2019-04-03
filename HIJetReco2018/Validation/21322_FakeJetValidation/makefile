FASTJET = /cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/
Partial = 100

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

RunHardProbes: Execute ExecutePlots
	./Execute --Input `ls HP_EEFix_NewMVA/*root | head -n $(Partial) | tr '\n' ','` \
		--Output Plots_HP_EEFix_NewMVA.root \
		--Tree "akCs4PFJetAnalyzer/t" \
		--MinPTForTrack 50 --Trigger HLT_HIPuAK4CaloJet100Eta5p1_v1
	./Execute --Input `ls HP_EEFix_NoMVA/*root | head -n $(Partial) | tr '\n' ','` \
		--Output Plots_HP_EEFix_NoMVA.root \
		--Tree "akCs4PFJetAnalyzer/t" \
		--MinPTForTrack 50 --Trigger HLT_HIPuAK4CaloJet100Eta5p1_v1
	./ExecutePlots --InputTarget Plots_HP_EEFix_NewMVA.root \
		--InputReference Plots_HP_EEFix_NoMVA.root \
		--Output HardProbes.pdf
	cp HardProbes.pdf ~/public/html
	./Execute --Input `ls HP_EEFix_NewMVA/*root | head -n $(Partial) | tr '\n' ','` \
		--Output Plots_HP_EEFix_NewMVA_Calo.root \
		--Tree "akPu4CaloJetAnalyzer/t" \
		--MinPTForTrack 500 --Trigger HLT_HIPuAK4CaloJet100Eta5p1_v1
	./Execute --Input `ls HP_EEFix_NoMVA/*root | head -n $(Partial) | tr '\n' ','` \
		--Output Plots_HP_EEFix_NoMVA_Calo.root \
		--Tree "akPu4CaloJetAnalyzer/t" \
		--MinPTForTrack 500 --Trigger HLT_HIPuAK4CaloJet100Eta5p1_v1
	./ExecutePlots --InputTarget Plots_HP_EEFix_NewMVA_Calo.root \
		--InputReference Plots_HP_EEFix_NoMVA_Calo.root \
		--Output HardProbes_Calo.pdf
	cp HardProbes_Calo.pdf ~/public/html

RunMB: Execute ExecutePlots
	./Execute --Input `ls MB_NoEEFix_NewMVA/*root | head -n $(Partial) | tr '\n' ','` \
		--Output Plots_MB_NoEEFix_NewMVA.root \
		--Tree "akCs4PFJetAnalyzer/t" \
		--MinPTForTrack 50 --Trigger NONE
	./Execute --Input `ls MB_NoEEFix_NoMVA/*root | head -n $(Partial) | tr '\n' ','` \
		--Output Plots_MB_NoEEFix_NoMVA.root \
		--Tree "akCs4PFJetAnalyzer/t" \
		--MinPTForTrack 50 --Trigger NONE
	./ExecutePlots --InputTarget Plots_MB_NoEEFix_NewMVA.root \
		--InputReference Plots_MB_NoEEFix_NoMVA.root \
		--Output MinimumBias.pdf
	cp MinimumBias.pdf ~/public/html/

RunMBNoTrack: Execute ExecutePlots
	./Execute --Input `ls MB_NoEEFix_NewMVA/*root | head -n $(Partial) | tr '\n' ','` \
		--Output Plots_MB_NoEEFix_NewMVA_NoTrack.root \
		--Tree "akCs4PFJetAnalyzer/t" \
		--MinPTForTrack 9999 --Trigger NONE
	./Execute --Input `ls MB_NoEEFix_NoMVA/*root | head -n $(Partial) | tr '\n' ','` \
		--Output Plots_MB_NoEEFix_NoMVA_NoTRack.root \
		--Tree "akCs4PFJetAnalyzer/t" \
		--MinPTForTrack 9999 --Trigger NONE
	./ExecutePlots --InputTarget Plots_MB_NoEEFix_NewMVA_NoTrack.root \
		--InputReference Plots_MB_NoEEFix_NoMVA_NoTrack.root \
		--Output MinimumBias.pdf
	cp MinimumBias.pdf ~/public/html/



