default: RunPlot

Execute: FillTrees.cpp HelperFunctions.o Histograms.o
	CompileRootMacro FillTrees.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`fastjet-config --cxxflags --libs` HelperFunctions.o Histograms.o

ExecutePlot: PlotDoublePhotonEfficiency.cpp
	CompileRootMacro PlotDoublePhotonEfficiency.cpp ExecutePlot

Histograms.o: Histograms.cpp Histograms.h
	CompileRootMacro Histograms.cpp Histograms.o -c

HelperFunctions.o: HelperFunctions.cpp HelperFunctions.h
	CompileRootMacro HelperFunctions.cpp HelperFunctions.o -c \
		-I../../CommonCode/include `fastjet-config --cxxflags`

RunTest: Execute
	./Execute --input `ls SamplesHGG/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` \
		--output HGG.root --StoredGen true

RunPlot: ExecutePlot
	./ExecutePlot --input HGG.root --output HGGPV.pdf --DoPV true --PT1 16 --PT2 13
	./ExecutePlot --input HGG.root --output HGGNonPV.pdf --DoPV false --PT1 14 --PT2 8
