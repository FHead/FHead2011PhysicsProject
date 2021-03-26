FJCONTRIB = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet-contrib/1.033-omkpbe

default: all

all: library/Messenger.o library/RhoCalculator.o library/JetProducer.o

library/Messenger.o: source/Messenger.cpp include/Messenger.h
	g++ source/Messenger.cpp -I. -c -o library/Messenger.o `root-config --cflags` -std=c++17

library/RhoCalculator.o: source/RhoCalculator.cpp include/RhoCalculator.h
	g++ source/RhoCalculator.cpp -I. -c -o library/RhoCalculator.o `$(FastJetConfig) --cxxflags` -std=c++17 \
		-I$(RootMacrosBase) \
		`root-config --cflags`

library/JetProducer.o: source/JetProducer.cpp include/JetProducer.h
	g++ source/JetProducer.cpp -I. -c -o library/JetProducer.o -std=c++17 \
		`$(FastJetConfig) --cxxflags` -I$(FJCONTRIB)/include \
		-I$(RootMacrosBase) \
		`root-config --cflags`
