FASTJET = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/fastjet-config

default: TestRun

FullRun: Execute
	for i in Data2018/200818_104315//000*/*; \
	do \
		echo $$i; \
		j=`echo $$i | cut -d '_' -f 3`; \
		./Execute --Input $$i --Output Output2018/JRA_$$j; \
	done

TestRun: Execute
	./Execute --Input Data2018/200818_104315//0000/HiForestAOD_993.root --Output /tmp/chenyi/JRA_993.root

Execute: Convert.cpp
	g++ Convert.cpp -o Execute \
		`root-config --cflags --glibs` \
		`$(FASTJET) --cxxflags --libs` \
		-I/afs/cern.ch/user/c/chenyi/RootMacros /afs/cern.ch/user/c/chenyi/RootMacros/Code/library/TauHelperFunctions3.o

CountInput:
	ls Data2018/*/000*/* | wc -l

PrepareSubmit:
	bash MakeSubmit2018.sh > Submit2018.condor
	bash MakeSubmit2017.sh > Submit2017.condor
