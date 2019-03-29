FASTJET = /cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/

ExecuteSkim: Skim.cpp
	CompileRootMacro Skim.cpp ExecuteSkim \
		`$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs` \
		-I../../CommonCode/include ../../CommonCode/library/*o

