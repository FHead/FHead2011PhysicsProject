Config     = 20200213.config

default: RunDYLL 

Execute: FillHistograms.cpp Histograms.o HelperFunctions.o
	CompileRootMacro FillHistograms.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`fastjet-config --cxxflags --libs` \
		Histograms.o HelperFunctions.o

Histograms.o: Histograms.cpp Histograms.h
	CompileRootMacro Histograms.cpp Histograms.o -c

HelperFunctions.o: HelperFunctions.cpp HelperFunctions.h
	CompileRootMacro HelperFunctions.cpp HelperFunctions.o -c \
		-I../../CommonCode/include `fastjet-config --cxxflags`

RunDYLL: Execute
	./Execute --input `ls SamplesDYLL/* | head -n 1000 | tr '\n' ',' | sed "s/,$$//g"` \
		--output /tmp/chenyi/DYLL.root --StoredGen true --config $(Config) \
		--tree true

