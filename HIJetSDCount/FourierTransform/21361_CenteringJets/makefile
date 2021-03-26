FASTJET = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/fastjet-config

default: TestRun

RunExport: ExportJet.cpp TreeMessenger.o
	# CompileRootMacro ExportJet.cpp RunExport TreeMessenger.o \
	# 	`$(FASTJET) --libs --cxxflags`
	g++ ExportJet.cpp -o RunExport TreeMessenger.o \
		`root-config --cflags --glibs` \
		`$(FASTJET) --libs --cxxflags` \
		-I/afs/cern.ch/user/c/chenyi/RootMacros/ ~/RootMacros/Code/library/*.o \
		-std=c++17

TreeMessenger.o: TreeMessenger.cpp
	# CompileRootMacro TreeMessenger.cpp TreeMessenger.o -c
	g++ TreeMessenger.cpp -c -o TreeMessenger.o `root-config --cflags`

TestRun: RunExport
	./RunExport Hydjet/60k_CentralFivePercent/RunOutput_0.root Pythia/Output.root TestOutput.root 0 19 0

Submit: RunExport
	for i in `seq 0 199`; do \
		Start=`echo $$i | MultiplyConst 300`; \
		End=`echo $$Start | AddConst 299`; \
		echo $$Start $$End; \
		cat RunFile.template | sed "s/__START__/$$Start/" \
	   	| sed "s/__END__/$$End/" | sed "s/__FILE__/$$i/" | bsub -q 8nh -J RunJetExport; \
	done


