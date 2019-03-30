FASTJET = /cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/

default: TestRun

TestRun: Execute
	./Execute --Input `ls PythiaQHatSplit/vac_ptbin_*/*root | tr '\n' ','` --OutputBase QPythiaVac
	./Execute --Input `ls PythiaQHatSplit/qhat1_ptbin_*/*root | tr '\n' ','` --OutputBase QPythiaQHat1
	cp QPythia*.pdf ~/public/html

Execute: Analyze.cpp
	CompileRootMacro Analyze.cpp Execute \
		`$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs` \
