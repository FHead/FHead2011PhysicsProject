
default: TestRunPlot

ExecutePlot: MakePValuePlot.cpp
	CompileRootMacro MakePValuePlot.cpp ExecutePlot

TestRunPlot: ExecutePlot
	./ExecutePlot --DHFile ResultsLBT.dh --Output PValueLBT.eps --Label LBT
	./ExecutePlot --DHFile ResultsMatter.dh --Output PValueMatter.eps --Label Matter
	./ExecutePlot --DHFile ResultsMatterLBT1.dh --Output PValueMatterLBT1.eps --Label 'Matter+LBT1'
	./ExecutePlot --DHFile ResultsMatterLBT2.dh --Output PValueMatterLBT2.eps --Label 'Matter+LBT2'
	epstopdf PValueLBT.eps
	epstopdf PValueMatter.eps
	epstopdf PValueMatterLBT1.eps
	epstopdf PValueMatterLBT2.eps

ExecuteExample: MakeExample.cpp
	CompileRootMacro MakeExample.cpp ExecuteExample

TestRunExample: ExecuteExample
	./ExecuteExample --N 72 \
		--Posterior txt/Result_LBT_72_*_PosteriorValues.txt \
		--Holdout txt/Result_LBT_72_*_HoldoutPosteriorValue.txt

Execute: ProcessFile.cpp
	g++ ProcessFile.cpp -I/Users/yichen/RootMacros -std=c++11 -o Execute

TestRun: Execute
	./Execute --DHFile Results.dh --N 9 \
		--Posterior txt/Result_LBT_9_*_PosteriorValues.txt \
		--Holdout txt/Result_LBT_9_*_HoldoutPosteriorValue.txt

FullRun: Execute
	for i in `seq 0 139`; \
	do \
		./Execute --DHFile ResultsLBT.dh --N $${i} \
			--Posterior txt/Result_LBT_$${i}_*_PosteriorValues.txt \
			--Holdout txt/Result_LBT_$${i}_*_HoldoutPosteriorValue.txt; \
	done
	for i in `seq 0 63`; \
	do \
		./Execute --DHFile ResultsMatter.dh --N $${i} \
			--Posterior txt/Result_Matter_$${i}_*_PosteriorValues.txt \
			--Holdout txt/Result_Matter_$${i}_*_HoldoutPosteriorValue.txt; \
	done
	for i in `seq 0 69`; \
	do \
		./Execute --DHFile ResultsMatterLBT1.dh --N $${i} \
			--Posterior txt/Result_MatterLBT1_$${i}_*_PosteriorValues.txt \
			--Holdout txt/Result_MatterLBT1_$${i}_*_HoldoutPosteriorValue.txt; \
	done
	for i in `seq 0 80`; \
	do \
		./Execute --DHFile ResultsMatterLBT2.dh --N $${i} \
			--Posterior txt/Result_MatterLBT2_$${i}_*_Alpha0.0_*_PosteriorValues.txt \
			--Holdout txt/Result_MatterLBT2_$${i}_*_Alpha0.0_*_HoldoutPosteriorValue.txt; \
	done



