PbPb_PF   = input/JEC_MCTruth_2018_etaClosure_L2L3_ak26PF.root
PP_PF     = input/JEC_MCTruth_pp2017_etaClosure_L2L3_ak26PF.root
PTBinning = 15,17,20,23,27,30,35,40,45,57,72,90,120,150,200,300,400,550

default: TestRun

TestRun: Execute
	./Execute --Input input/JEC_MCTruth_2018_etaClosure_L2L3_ak26PF.root \
		--Output PbPbAK4PF.txt \
		--Algorithm ak4pf --Plots Plots_AK4PF.pdf \
		--PTBinning "15,17,20,23,27,30,35,40,45,57,72,90,120,150,200,300,400,550" \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	cp Plots_AK4PF.pdf ~/public/html/

RunAll: Execute
	./Execute --Input $(PbPb_PF) --Output PbPbAK2PF.txt \
		--Algorithm ak2pf --Plots Plots_PbPb_AK2PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PbPb_PF) --Output PbPbAK3PF.txt \
		--Algorithm ak3pf --Plots Plots_PbPb_AK3PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PbPb_PF) --Output PbPbAK4PF.txt \
		--Algorithm ak4pf --Plots Plots_PbPb_AK4PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PbPb_PF) --Output PbPbAK5PF.txt \
		--Algorithm ak5pf --Plots Plots_PbPb_AK5PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PbPb_PF) --Output PbPbAK6PF.txt \
		--Algorithm ak6pf --Plots Plots_PbPb_AK6PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output PPAK2PF.txt \
		--Algorithm ak2pf --Plots Plots_PP_AK2PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output PPAK3PF.txt \
		--Algorithm ak3pf --Plots Plots_PP_AK3PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output PPAK4PF.txt \
		--Algorithm ak4pf --Plots Plots_PP_AK4PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output PPAK5PF.txt \
		--Algorithm ak5pf --Plots Plots_PP_AK5PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output PPAK6PF.txt \
		--Algorithm ak6pf --Plots Plots_PP_AK6PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	cp Plots*AK*PF.pdf ~/public/html/

RunAllData: Execute
	./Execute --Input $(PbPb_PF) --Output DataPbPbAK2PF.txt \
		--Algorithm ak2pf --Plots Plots_DataPbPb_AK2PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PbPb_PF) --Output DataPbPbAK3PF.txt \
		--Algorithm ak3pf --Plots Plots_DataPbPb_AK3PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PbPb_PF) --Output DataPbPbAK4PF.txt \
		--Algorithm ak4pf --Plots Plots_DataPbPb_AK4PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PbPb_PF) --Output DataPbPbAK5PF.txt \
		--Algorithm ak5pf --Plots Plots_DataPbPb_AK5PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PbPb_PF) --Output DataPbPbAK6PF.txt \
		--Algorithm ak6pf --Plots Plots_DataPbPb_AK6PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output DataPPAK2PF.txt \
		--Algorithm ak2pf --Plots Plots_DataPP_AK2PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output DataPPAK3PF.txt \
		--Algorithm ak3pf --Plots Plots_DataPP_AK3PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output DataPPAK4PF.txt \
		--Algorithm ak4pf --Plots Plots_DataPP_AK4PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output DataPPAK5PF.txt \
		--Algorithm ak5pf --Plots Plots_DataPP_AK5PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	./Execute --Input $(PP_PF) --Output DataPPAK6PF.txt \
		--Algorithm ak6pf --Plots Plots_DataPP_AK6PF.pdf \
		--PTBinning $(PTBinning) \
		--Constant 0.005 --Scale 1.10 --Cutoff 21 --Cutoff2 31
	cp Plots*AK*PF.pdf ~/public/html/

Execute: EstimateUncertainty.cpp
	CompileRootMacro EstimateUncertainty.cpp Execute
