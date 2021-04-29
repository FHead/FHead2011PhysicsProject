
default: ExecuteConversion ExecuteBasicPlots ExecuteJetClustering ExecuteJetPlots

DrawRandom.o: DrawRandom.cpp DrawRandom.h
	g++ DrawRandom.cpp -c -o DrawRandom.o -std=c++11

DrawRandom2.o: DrawRandom2.cpp DrawRandom2.h
	g++ DrawRandom2.cpp -c -o DrawRandom2.o -std=c++11

TauHelperFunctions3.o: TauHelperFunctions3.cpp TauHelperFunctions3.h
	g++ TauHelperFunctions3.cpp -c -o TauHelperFunctions3.o -std=c++11

CATree.o: CATree.cpp CATree.h
	g++ CATree.cpp -c -o CATree.o -std=c++11

BasicUtilities.o: BasicUtilities.cpp BasicUtilities.h
	g++ BasicUtilities.cpp -c -o BasicUtilities.o -std=c++11

Dictionary.o: Dictionary.h DictionaryObject.h
	rootcint -f Dictionary.cxx -c DictionaryObject.h Dictionary.h
	g++ `root-config --cflags` Dictionary.cxx -o Dictionary.o -I. -c -fpic

ExecuteConversion: ConvertToTree.cpp TauHelperFunctions3.o DrawRandom2.o Dictionary.o
	g++ ConvertToTree.cpp `root-config --cflags --glibs` -o ExecuteConversion TauHelperFunctions3.o DrawRandom2.o Dictionary.o

ExecuteBasicPlots: MakeBasicPlots.cpp TauHelperFunctions3.o DrawRandom2.o Dictionary.o
	g++ MakeBasicPlots.cpp `root-config --cflags --glibs` -o ExecuteBasicPlots TauHelperFunctions3.o DrawRandom2.o Dictionary.o

ExecuteJetClustering: CalculateJets.cpp TauHelperFunctions3.o DrawRandom2.o DrawRandom.o CATree.o BasicUtilities.o Dictionary.o
	g++ CalculateJets.cpp `root-config --cflags --glibs` -o ExecuteJetClustering \
		TauHelperFunctions3.o DrawRandom2.o CATree.o DrawRandom.o BasicUtilities.o Dictionary.o \
		`fastjet-config --cxxflags --libs`

ExecuteJetPlots: MakeJetPlots.cpp Dictionary.o
	g++ MakeJetPlots.cpp `root-config --cflags --glibs` -o ExecuteJetPlots Dictionary.o

