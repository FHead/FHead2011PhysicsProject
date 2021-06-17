FASTJET = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/
TestN = 100000

default: TestHydjet

ReadPU14Event.o: ReadPU14Event.cpp ReadPU14Event.h
	g++ ReadPU14Event.cpp -c -o ReadPU14Event.o \
		-I/afs/cern.ch/user/c/chenyi/RootMacros

Execute: Analyze.cpp ReadPU14Event.o
	CompileRootMacro Analyze.cpp Execute ReadPU14Event.o \
		`$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs`

TestRun: Execute
	./Execute --InputPythia Samples/pythia8/dijet30/PythiaEventsTune14PtHat30_1.pu14 \
		--InputBackground Samples/Background/Mult7000/BackgroundEventsMult7000PtAv1.20_1.pu14 \
		--Output TestResult1.root --MaxEvent $(TestN)
	./Execute --InputPythia Samples/pythia8/dijet50/PythiaEventsTune14PtHat50_1.pu14 \
		--InputBackground Samples/Background/Mult7000/BackgroundEventsMult7000PtAv1.20_1.pu14 \
		--Output TestResult2.root --MaxEvent $(TestN)
	./Execute --InputPythia Samples/pythia8/dijet80/PythiaEventsTune14PtHat80_1.pu14 \
		--InputBackground Samples/Background/Mult7000/BackgroundEventsMult7000PtAv1.20_1.pu14 \
		--Output TestResult3.root --MaxEvent $(TestN)
	./Execute --InputPythia Samples/pythia8/dijet120/PythiaEventsTune14PtHat120_1.pu14 \
		--InputBackground Samples/Background/Mult7000/BackgroundEventsMult7000PtAv1.20_1.pu14 \
		--Output TestResult4.root --MaxEvent $(TestN)
	./Execute --InputPythia Samples/pythia8/dijet200/PythiaEventsTune14PtHat200_1.pu14 \
		--InputBackground Samples/Background/Mult7000/BackgroundEventsMult7000PtAv1.20_1.pu14 \
		--Output TestResult5.root --MaxEvent $(TestN)
	hadd -f TestResult.root TestResult[1-5].root

TestHydjet: Execute
	./Execute --InputPythia Samples/pythia8/dijet30/PythiaEventsTune14PtHat30_1.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjet1.root --MaxEvent $(TestN)
	./Execute --InputPythia Samples/pythia8/dijet50/PythiaEventsTune14PtHat50_1.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjet2.root --MaxEvent $(TestN)
	./Execute --InputPythia Samples/pythia8/dijet80/PythiaEventsTune14PtHat80_1.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjet3.root --MaxEvent $(TestN)
	./Execute --InputPythia Samples/pythia8/dijet120/PythiaEventsTune14PtHat120_1.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjet4.root --MaxEvent $(TestN)
	./Execute --InputPythia Samples/pythia8/dijet200/PythiaEventsTune14PtHat200_1.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjet5.root --MaxEvent $(TestN)
	hadd -f TestHydjet.root TestHydjet[1-5].root

TestHydjetGJ: Execute
	./Execute --InputPythia Samples/ToyBackground/PhotonJet15.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjetGJ1.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.999456
	./Execute --InputPythia Samples/ToyBackground/PhotonJet30.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjetGJ2.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.186121
	./Execute --InputPythia Samples/ToyBackground/PhotonJet50.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjetGJ3.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.0422225
	./Execute --InputPythia Samples/ToyBackground/PhotonJet80.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjetGJ4.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.00931044
	./Execute --InputPythia Samples/ToyBackground/PhotonJet120.pu14 \
		--InputBackground Samples/ToyBackground/Toy10000.pu14 \
		--Output TestHydjetGJ5.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.00194072
	hadd -f TestHydjetGJ.root TestHydjetGJ[1-5].root

TestHydjetGJCentral: Execute
	./Execute --InputPythia Samples/ToyBackground/PhotonJet15.pu14 \
		--InputBackground Samples/ToyBackground/CentralToy10000.pu14 \
		--Output TestHydjetGJCentral1.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.999456
	./Execute --InputPythia Samples/ToyBackground/PhotonJet30.pu14 \
		--InputBackground Samples/ToyBackground/CentralToy10000.pu14 \
		--Output TestHydjetGJCentral2.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.186121
	./Execute --InputPythia Samples/ToyBackground/PhotonJet50.pu14 \
		--InputBackground Samples/ToyBackground/CentralToy10000.pu14 \
		--Output TestHydjetGJCentral3.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.0422225
	./Execute --InputPythia Samples/ToyBackground/PhotonJet80.pu14 \
		--InputBackground Samples/ToyBackground/CentralToy10000.pu14 \
		--Output TestHydjetGJCentral4.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.00931044
	./Execute --InputPythia Samples/ToyBackground/PhotonJet120.pu14 \
		--InputBackground Samples/ToyBackground/CentralToy10000.pu14 \
		--Output TestHydjetGJCentral5.root --MaxEvent $(TestN) --TagIsJet false --Weight 0.00194072
	hadd -f TestHydjetGJCentral.root TestHydjetGJCentral[1-5].root

