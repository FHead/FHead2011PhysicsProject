FASTJET = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/fastjet-config

default: Execute
	./Execute --input HiForestAODTest.root
	
Execute: DoPlaneFit.cpp
	CompileRootMacro DoPlaneFit.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`$(FASTJET) --cxxflags --libs`
