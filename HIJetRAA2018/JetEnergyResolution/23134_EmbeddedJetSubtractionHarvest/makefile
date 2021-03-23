

default: RunSummary

RunTest: ExecuteSummary
	bash RunPhiComparison.sh 040 PT Eta0+Centrality0 50 1000

RunSummaryCentrality: ExecuteSummary
	./ExecuteSummary --scan Centrality \
		--input R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh \
		--label "0.0-0.5","0.5-1.0","1.0-1.5","1.5-2.0","2.0-2.5","2.5-3.0" \
		--restriction "PT2+Eta0","PT2+Eta1","PT2+Eta2","PT2+Eta3","PT2+Eta4","PT2+Eta5" \
		--plot "Mean" \
		--output R040_Centrality_PT2_EtaBins_Mean \
		--title "PT = [100, 200];Centrality (%);Mean" --xmin 0 --xmax 1 --ymin 0.75 --ymax 1.25
	./ExecuteSummary --scan Centrality \
		--input R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh \
		--label "0.0-0.5","0.5-1.0","1.0-1.5","1.5-2.0","2.0-2.5","2.5-3.0" \
		--restriction "PT3+Eta0","PT3+Eta1","PT3+Eta2","PT3+Eta3","PT3+Eta4","PT3+Eta5" \
		--plot "Mean" \
		--output R040_Centrality_PT3_EtaBins_Mean \
		--title "PT = [200, 300];Centrality (%);Mean" --xmin 0 --xmax 1 --ymin 0.75 --ymax 1.25
	./ExecuteSummary --scan Centrality \
		--input R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh \
		--label "0.0-0.5","0.5-1.0","1.0-1.5","1.5-2.0","2.0-2.5","2.5-3.0" \
		--restriction "PT4+Eta0","PT4+Eta1","PT4+Eta2","PT4+Eta3","PT4+Eta4","PT4+Eta5" \
		--plot "Mean" \
		--output R040_Centrality_PT4_EtaBins_Mean \
		--title "PT = [300, 500];Centrality (%);Mean" --xmin 0 --xmax 1 --ymin 0.75 --ymax 1.25
	./ExecuteSummary --scan Centrality \
		--input R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh,R040_NominalPhi.dh \
		--label "0.0-0.5","0.5-1.0","1.0-1.5","1.5-2.0","2.0-2.5","2.5-3.0" \
		--restriction "PT2+Eta0","PT2+Eta1","PT2+Eta2","PT2+Eta3","PT2+Eta4","PT2+Eta5" \
		--plot "RMS" \
		--output R040_Centrality_PT2_EtaBins_RMS \
		--title "PT = [100, 200];Centrality (%);RMS" --xmin 0 --xmax 1 --ymin 0.0 --ymax 0.75

RunSummary: ExecuteSummary
	bash RunPhiComparison.sh 040 DPhi PT2+Eta0+Centrality0 0 3.14159
	bash RunPhiComparison.sh 040 DPhi PT2+Eta0+Centrality1 0 3.14159
	bash RunPhiComparison.sh 040 DPhi PT2+Eta0+Centrality2 0 3.14159
	bash RunPhiComparison.sh 040 DPhi PT2+Eta0+Centrality3 0 3.14159
	# bash RunPhiComparison.sh 015 PT Eta0+Centrality0 50 1000
	# bash RunPhiComparison.sh 015 PT Eta0+Centrality1 50 1000
	# bash RunPhiComparison.sh 015 PT Eta0+Centrality2 50 1000
	# bash RunPhiComparison.sh 015 PT Eta0+Centrality3 50 1000
	# bash RunPhiComparison.sh 015 Eta PT2+Centrality0 -3 3
	# bash RunPhiComparison.sh 015 Eta PT2+Centrality1 -3 3
	# bash RunPhiComparison.sh 015 Eta PT2+Centrality2 -3 3
	# bash RunPhiComparison.sh 015 Eta PT2+Centrality3 -3 3
	# bash RunPhiComparison.sh 040 PT Eta0+Centrality0 50 1000
	# bash RunPhiComparison.sh 040 PT Eta0+Centrality1 50 1000
	# bash RunPhiComparison.sh 040 PT Eta0+Centrality2 50 1000
	# bash RunPhiComparison.sh 040 PT Eta0+Centrality3 50 1000
	# bash RunPhiComparison.sh 040 Eta PT2+Centrality0 -3 3
	# bash RunPhiComparison.sh 040 Eta PT2+Centrality1 -3 3
	# bash RunPhiComparison.sh 040 Eta PT2+Centrality2 -3 3
	# bash RunPhiComparison.sh 040 Eta PT2+Centrality3 -3 3
	# bash RunPhiComparison.sh 040 Centrality PT2+Eta0 0 1
	# bash RunPhiComparison.sh 040 Centrality PT2+Eta1 0 1
	# bash RunPhiComparison.sh 040 Centrality PT2+Eta2 0 1
	# bash RunPhiComparison.sh 040 Centrality PT2+Eta3 0 1
	# bash RunPhiComparison.sh 040 Centrality PT2+Eta4 0 1
	# bash RunPhiComparison.sh 040 Centrality PT2+Eta5 0 1
	# bash RunPhiComparison.sh 120 PT Eta0+Centrality0 99 1000
	# bash RunPhiComparison.sh 120 PT Eta0+Centrality1 99 1000
	# bash RunPhiComparison.sh 120 PT Eta0+Centrality2 99 1000
	# bash RunPhiComparison.sh 120 PT Eta0+Centrality3 99 1000
	# bash RunPhiComparison.sh 120 Eta PT2+Centrality0 -3 3
	# bash RunPhiComparison.sh 120 Eta PT2+Centrality1 -3 3
	# bash RunPhiComparison.sh 120 Eta PT2+Centrality2 -3 3
	# bash RunPhiComparison.sh 120 Eta PT2+Centrality3 -3 3
	# bash RunEtaComparison.sh 040 Centrality PT1 0 1 NoPhi
	# bash RunEtaComparison.sh 040 Centrality PT2 0 1 NoPhi
	# bash RunEtaComparison.sh 040 Centrality PT3 0 1 NoPhi
	# bash RunEtaComparison.sh 040 PT Centrality0 99 1000 NoPhi
	# bash RunEtaComparison.sh 040 PT Centrality1 99 1000 NoPhi
	# bash RunEtaComparison.sh 040 PT Centrality2 99 1000 NoPhi
	# bash RunEtaComparison.sh 040 PT Centrality3 99 1000 NoPhi
	# bash RunEtaComparison.sh 040 Centrality PT1 0 1 NominalPhi
	# bash RunEtaComparison.sh 040 Centrality PT2 0 1 NominalPhi
	# bash RunEtaComparison.sh 040 Centrality PT3 0 1 NominalPhi
	# bash RunEtaComparison.sh 040 PT Centrality0 99 1000 NominalPhi
	# bash RunEtaComparison.sh 040 PT Centrality1 99 1000 NominalPhi
	# bash RunEtaComparison.sh 040 PT Centrality2 99 1000 NominalPhi
	# bash RunEtaComparison.sh 040 PT Centrality3 99 1000 NominalPhi
	# bash RunEtaComparison.sh 040 Centrality PT1 0 1 WidePhi
	# bash RunEtaComparison.sh 040 Centrality PT2 0 1 WidePhi
	# bash RunEtaComparison.sh 040 Centrality PT3 0 1 WidePhi
	# bash RunEtaComparison.sh 040 PT Centrality0 99 1000 WidePhi
	# bash RunEtaComparison.sh 040 PT Centrality1 99 1000 WidePhi
	# bash RunEtaComparison.sh 040 PT Centrality2 99 1000 WidePhi
	# bash RunEtaComparison.sh 040 PT Centrality3 99 1000 WidePhi
	cp *pdf ~/public/html/

Run015: Execute
	./Execute --input `ls Output/R015_NoPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R015_NoPhi.dh
	./Execute --input `ls Output/R015_NominalPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R015_NominalPhi.dh
	./Execute --input `ls Output/R015_WidePhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R015_WidePhi.dh

Run020: Execute
	./Execute --input `ls Output/R020_NoPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R020_NoPhi.dh
	./Execute --input `ls Output/R020_NominalPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R020_NominalPhi.dh
	./Execute --input `ls Output/R020_WidePhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R020_WidePhi.dh

Run030: Execute
	./Execute --input `ls Output/R030_NoPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R030_NoPhi.dh
	./Execute --input `ls Output/R030_NominalPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R030_NominalPhi.dh
	./Execute --input `ls Output/R030_WidePhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R030_WidePhi.dh

Run040: Execute
	./Execute --input `ls Output/R040_NoPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R040_NoPhi.dh
	./Execute --input `ls Output/R040_NominalPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R040_NominalPhi.dh
	./Execute --input `ls Output/R040_WidePhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R040_WidePhi.dh

Run050: Execute
	./Execute --input `ls Output/R050_NoPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R050_NoPhi.dh
	./Execute --input `ls Output/R050_NominalPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R050_NominalPhi.dh
	./Execute --input `ls Output/R050_WidePhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R050_WidePhi.dh

Run060: Execute
	./Execute --input `ls Output/R060_NoPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R060_NoPhi.dh
	./Execute --input `ls Output/R060_NominalPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R060_NominalPhi.dh
	./Execute --input `ls Output/R060_WidePhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R060_WidePhi.dh

Run080: Execute
	./Execute --input `ls Output/R080_NoPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R080_NoPhi.dh
	./Execute --input `ls Output/R080_NominalPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R080_NominalPhi.dh
	./Execute --input `ls Output/R080_WidePhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R080_WidePhi.dh

Run100: Execute
	./Execute --input `ls Output/R100_NoPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R100_NoPhi.dh
	./Execute --input `ls Output/R100_NominalPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R100_NominalPhi.dh
	./Execute --input `ls Output/R100_WidePhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R100_WidePhi.dh

Run120: Execute
	./Execute --input `ls Output/R120_NoPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R120_NoPhi.dh
	./Execute --input `ls Output/R120_NominalPhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R120_NominalPhi.dh
	./Execute --input `ls Output/R120_WidePhi/*root | tr '\n' ',' | sed "s/,$$//"` --output R120_WidePhi.dh

TestRunPlot: ExecutePlot
	./ExecutePlot --input R040_NoPhi.dh --output Plot040_NoPhi.pdf
	./ExecutePlot --input R040_NominalPhi.dh --output Plot040_NominalPhi.pdf
	./ExecutePlot --input R040_WidePhi.dh --output Plot040_WidePhi.pdf
	cp *pdf ~/public/html

Execute: JetResolution.cpp
	CompileRootMacro JetResolution.cpp Execute

ExecutePlot: PlotSingleResolution.cpp
	CompileRootMacro PlotSingleResolution.cpp ExecutePlot

ExecuteSummary: PlotResolution.cpp
	CompileRootMacro PlotResolution.cpp ExecuteSummary

