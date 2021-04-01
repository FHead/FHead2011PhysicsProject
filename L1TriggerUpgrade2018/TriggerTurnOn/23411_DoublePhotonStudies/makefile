default: RunTest 

Execute: FillTrees.cpp HelperFunctions.o Histograms.o
	CompileRootMacro FillTrees.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`fastjet-config --cxxflags --libs` HelperFunctions.o Histograms.o

Histograms.o: Histograms.cpp Histograms.h
	CompileRootMacro Histograms.cpp Histograms.o -c

HelperFunctions.o: HelperFunctions.cpp HelperFunctions.h
	CompileRootMacro HelperFunctions.cpp HelperFunctions.o -c \
		-I../../CommonCode/include `fastjet-config --cxxflags`

RunTest: Execute
	./Execute --input `ls SamplesHGG/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` \
		--output HGG.root --StoredGen true

