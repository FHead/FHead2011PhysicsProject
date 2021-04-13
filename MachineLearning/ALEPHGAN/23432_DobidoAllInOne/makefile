
default: ExecuteConversion ExecuteBasicPlots ExecuteJetClustering ExecuteJetPlots

DrawRandom.o: DrawRandom.cpp DrawRandom.h
	g++ DrawRandom.cpp -c -o DrawRandom.o

DrawRandom2.o: DrawRandom2.cpp DrawRandom2.h
	g++ DrawRandom2.cpp -c -o DrawRandom2.o

TauHelperFunctions3.o: TauHelperFunctions3.cpp TauHelperFunctions3.h
	g++ TauHelperFunctions3.cpp -c -o TauHelperFunctions3.o

CATree.o: CATree.cpp CATree.h
	g++ CATree.cpp -c -o CATree.o -std=c++11

BasicUtilities.o: BasicUtilities.cpp BasicUtilities.h
	g++ BasicUtilities.cpp -c -o BasicUtilities.o

Dictionary.o: Dictionary.h DictionaryObject.h
	rootcint -f Dictionary.cxx -c DictionaryObject.h Dictionary.h
	g++ `root-config --cflags` Dictionary.cxx -o Dictionary.o -I. -c -fpic

ExecuteConversion: ConvertToTree.cpp TauHelperFunctions3.o DrawRandom2.o Dictionary.o
	g++ `root-config --cflags --libs` ConvertToTree.cpp -o ExecuteConversion TauHelperFunctions3.o DrawRandom2.o Dictionary.o

ExecuteBasicPlots: MakeBasicPlots.cpp TauHelperFunctions3.o DrawRandom2.o Dictionary.o
	g++ `root-config --cflags --libs` MakeBasicPlots.cpp -o ExecuteBasicPlots TauHelperFunctions3.o DrawRandom2.o Dictionary.o

ExecuteJetClustering: CalculateJets.cpp TauHelperFunctions3.o DrawRandom2.o DrawRandom.o CATree.o BasicUtilities.o Dictionary.o
	g++ `root-config --cflags --libs` CalculateJets.cpp -o ExecuteJetClustering \
		TauHelperFunctions3.o DrawRandom2.o CATree.o DrawRandom.o BasicUtilities.o Dictionary.o \
		`fastjet-config --cxxflags --libs`

ExecuteJetPlots: MakeJetPlots.cpp Dictionary.o
	g++ `root-config --cflags --libs` MakeJetPlots.cpp -o ExecuteJetPlots Dictionary.o

