default: TestRunHistograms 

Execute: FillHistograms.cpp Histograms.o
	CompileRootMacro FillHistograms.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`fastjet-config --cxxflags --libs` \
		Histograms.o

Histograms.o: Histograms.cpp
	CompileRootMacro Histograms.cpp Histograms.o -c

TestRunHistograms: Execute
	./Execute --input SamplesTTbar/L1Ntuple_13.root --output TestRunHistograms.root

FullRunHistograms: Execute
	mkdir -p Result/
	for i in `ls SamplesTTbar/`; do echo $$i; ./Execute --input SamplesTTbar/$$i --output Result/$$i; done
	hadd -f TTbar.root Result/*root

