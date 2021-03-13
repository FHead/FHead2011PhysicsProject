

default: TestRun

TestRunMC: Execute
	time ./Execute --input 2018PbPbMBMC/HiForestAOD_1.root,2018PbPbMBMC/HiForestAOD_2.root,2018PbPbMBMC/HiForestAOD_3.root,2018PbPbMBMC/HiForestAOD_4.root,2018PbPbMBMC/HiForestAOD_46.root,2018PbPbMBMC/HiForestAOD_47.root,2018PbPbMBMC/HiForestAOD_48.root,2018PbPbMBMC/HiForestAOD_60.root \
		--output /tmp/chenyi/ResultMC.root --n 50 --nrho 250

TestRunData: Execute
	time ./Execute --input 2018PbPbMBData/0000/HiForestAOD_114.root,2018PbPbMBData/0000/HiForestAOD_125.root,2018PbPbMBData/0000/HiForestAOD_214.root,2018PbPbMBData/0000/HiForestAOD_225.root,2018PbPbMBData/0000/HiForestAOD_314.root,2018PbPbMBData/0000/HiForestAOD_325.root \
		--output /tmp/chenyi/ResultData.root --n 50 --data true --nrho 250

TestRun: Execute
	time ./Execute --input 2018PbPbMBData/0000/HiForestAOD_114.root \
		--output ResultTest.root --n 50 --data true --fraction 0.1 --nrho 250

Execute: DoRandomCone.cpp
	CompileRootMacro DoRandomCone.cpp Execute \
		-I../../CommonCode/include/ \
		../../CommonCode/library/*.o \
		`$(FastJetConfig) --cxxflags --libs`



