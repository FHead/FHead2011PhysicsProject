default: TestRunHistograms 

Execute: FillHistograms.cpp Histograms.o
	CompileRootMacro FillHistograms.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`fastjet-config --cxxflags --libs` \
		Histograms.o

Histograms.o: Histograms.cpp
	CompileRootMacro Histograms.cpp Histograms.o -c

TestRunHistograms: Execute
	./Execute --input Samples/L1Ntuple_99.root --output TestRunHistograms.root

FullRunHistograms: Execute
	mkdir -p Result/
	for i in `ls Samples/`; do echo $$i; ./Execute --input Samples/$$i --output Result/$$i; done
	hadd -f TTbar.root Result/*root

