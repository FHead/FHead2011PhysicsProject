FASTJET = /cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/

default: RunTest

RunTest: Execute
	./Execute --Input Output/Result_53.root --Output TestRun.root

RunRnD: Execute
	./Execute --Input RnD.root --Output RnDPlots.root

RunAll: Execute
	./Execute --Input `ls Output/*/*root | tr '\n' ','` --Output AllRun.root \
		--JetPTMin 30

RunPythia: Execute
	./Execute --Input `ls PythiaOutput/Result_*_GEN.root | tr '\n' ','` --Output PythiaAllRun.root \
		--JetPTMin 30

RunPythiaWeighted: Execute
	./Execute --Input `ls PythiaWeightedOutput/Result_*_GEN.root | tr '\n' ','` --Output PythiaWeightedAllRun.root \
		--JetPTMin 30

Execute: Skim.cpp
	CompileRootMacro Skim.cpp Execute \
		`$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs` \
		-I../../CommonCode/include ../../CommonCode/library/*o

