FASTJET = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/fastjet-config

default: TestRun

TestRun: Execute
	./Execute --input HiForestAOD.root

Execute: RunRhoReproduction.cpp RhoCalculator.o
	rm -f Execute
	CompileRootMacro RunRhoReproduction.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`$(FASTJET) --cxxflags --libs` RhoCalculator.o

RhoCalculator.o: RhoCalculator.h RhoCalculator.cpp
	g++ RhoCalculator.cpp -c -o RhoCalculator.o `$(FASTJET) --cxxflags` -I$(RootMacrosBase)/
