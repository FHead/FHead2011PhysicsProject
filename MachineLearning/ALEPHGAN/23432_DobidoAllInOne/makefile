
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

ExecuteConversion: ConvertToTree.cpp TauHelperFunctions3.o DrawRandom2.o
	g++ `root-config --cflags --libs` ConvertToTree.cpp -o ExecuteConversion TauHelperFunctions3.o DrawRandom2.o

ExecuteBasicPlots: MakeBasicPlots.cpp TauHelperFunctions3.o DrawRandom2.o
	g++ `root-config --cflags --libs` MakeBasicPlots.cpp -o ExecuteBasicPlots TauHelperFunctions3.o DrawRandom2.o

ExecuteJetClustering: CalculateJets.cpp TauHelperFunctions3.o DrawRandom2.o DrawRandom.o CATree.o BasicUtilities.o
	g++ `root-config --cflags --libs` CalculateJets.cpp -o ExecuteJetClustering \
		TauHelperFunctions3.o DrawRandom2.o CATree.o DrawRandom.o BasicUtilities.o \
		`fastjet-config --cxxflags --libs`

ExecuteJetPlots: MakeJetPlots.cpp
	g++ `root-config --cflags --libs` MakeJetPlots.cpp -o ExecuteJetPlots

