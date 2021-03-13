Lumi = 0.023
TAA3 = 0.100719
TAA2 = 0.051233
TAA1 = 0.025341
TAA0 = 0.018646

default: TestRun

TestRun: Execute
	./Execute --Input RAA_Smooth.root --Output RAA_R2_C0.txt \
		--Name "akCs2PU3PFFlowJetAnalyzer_Cent0to10" \
		--Smearing 0.01 --Lumi $(Lumi) --TAA $(TAA0)

FullRun: Execute
	for i in 2 3 4 6 8 10; \
	do \
		./Execute --Input RAA_Smooth.root --Output RAA_R$${i}_C0.txt \
			--Name "akCs$${i}PU3PFFlowJetAnalyzer_Cent0to10" \
			--Smearing 0.01 --Lumi $(Lumi) --TAA $(TAA0); \
		./Execute --Input RAA_Smooth.root --Output RAA_R$${i}_C1.txt \
			--Name "akCs$${i}PU3PFFlowJetAnalyzer_Cent10to30" \
			--Smearing 0.01 --Lumi $(Lumi) --TAA $(TAA1); \
		./Execute --Input RAA_Smooth.root --Output RAA_R$${i}_C2.txt \
			--Name "akCs$${i}PU3PFFlowJetAnalyzer_Cent30to50" \
			--Smearing 0.01 --Lumi $(Lumi) --TAA $(TAA2); \
		./Execute --Input RAA_Smooth.root --Output RAA_R$${i}_C3.txt \
			--Name "akCs$${i}PU3PFFlowJetAnalyzer_Cent50to90" \
			--Smearing 0.01 --Lumi $(Lumi) --TAA $(TAA3); \
	done
   
Execute: ExportTextFile.cpp
	CompileRootMacro ExportTextFile.cpp Execute
