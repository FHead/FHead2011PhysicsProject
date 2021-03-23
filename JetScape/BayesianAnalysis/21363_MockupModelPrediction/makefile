FASTJET = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/fastjet-config
PYTHIA8 = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/pythia8/230-ogkkac3/bin/pythia8-config

default: TestRun

TestRun: Execute
	./Execute

Execute: GeneratePythia.cpp
	g++ GeneratePythia.cpp -o Execute \
		`root-config --cflags --libs` \
		`$(FASTJET) --cxxflags --libs` \
		/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/pythia8/230-ogkkac3/lib/* \
		-I/cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/pythia8/230-ogkkac3/include \
		-I/afs/cern.ch/user/c/chenyi/RootMacros/ /afs/cern.ch/user/c/chenyi/RootMacros/Code/library/*.o
