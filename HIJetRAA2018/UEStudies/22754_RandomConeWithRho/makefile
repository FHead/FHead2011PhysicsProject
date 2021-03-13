

default: TestRunPlot

TestRunPlot: ExecutePlot
	./ExecutePlot --input ResultMC.root --output RandomConePlots.pdf --curves CurvesMC.root
	./ExecutePlot --input ResultData.root --output RandomConeDataPlots.pdf --curves CurvesData.root
	cp RandomCone*.pdf ~/public/html/

TestRunMC: Execute
	time ./Execute --input 2018PbPbMBMC/HiForestAOD_1.root,2018PbPbMBMC/HiForestAOD_2.root,2018PbPbMBMC/HiForestAOD_3.root,2018PbPbMBMC/HiForestAOD_4.root,2018PbPbMBMC/HiForestAOD_46.root,2018PbPbMBMC/HiForestAOD_47.root,2018PbPbMBMC/HiForestAOD_48.root,2018PbPbMBMC/HiForestAOD_60.root \
		--output ResultMC.root --n 50

TestRunData: Execute
	time ./Execute --input 2018PbPbMBData/0000/HiForestAOD_114.root,2018PbPbMBData/0000/HiForestAOD_125.root,2018PbPbMBData/0000/HiForestAOD_214.root,2018PbPbMBData/0000/HiForestAOD_225.root,2018PbPbMBData/0000/HiForestAOD_314.root,2018PbPbMBData/0000/HiForestAOD_325.root \
		--output ResultData.root --n 50 --data true

RunData: Execute
	time ./Execute --input `ls 2018PbPbMBData/000*/*root | head -n 20 | tr '\n' ',' | sed 's/,$$//'` \
		--output ResultData.root --n 50 --data true

CopyMC:
	cp `ls 2018PbPbMBMC/*root | head -n 10` /tmp/chenyi/

RunMC: Execute
	time ./Execute --input `ls 2018PbPbMBMC/*root | head -n 10 | tr '\n' ',' | sed 's/,$$//'` \
		--output ResultMC.root --n 50 --data false

RunCopiedMC: Execute
	time ./Execute --input `ls /tmp/chenyi/*root | tr '\n' ',' | sed 's/,$$//'` \
		--output ResultMC.root --n 50 --data false

ExecutePlot: DoRandomConePlots.cpp
	CompileRootMacro DoRandomConePlots.cpp ExecutePlot

Execute: DoRandomCone.cpp
	CompileRootMacro DoRandomCone.cpp Execute \
		-I../../CommonCode/include/ \
		../../CommonCode/library/*.o \
		`$(FastJetConfig) --cxxflags --libs`



