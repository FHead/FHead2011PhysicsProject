default: TestRunHistograms 

Execute: FillHistograms.cpp Histograms.o
	CompileRootMacro FillHistograms.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`fastjet-config --cxxflags --libs` \
		Histograms.o

Histograms.o: Histograms.cpp
	CompileRootMacro Histograms.cpp Histograms.o -c

TestRunHistograms: Execute
	./Execute --input SamplesTTbar/L1Ntuple_14.root --output TestRunHistograms.root

FullRunHistogramsTTbar: Execute
	mkdir -p Result/
	rm -f Result/*root
	for i in `ls SamplesTTbar/`; do echo $$i; ./Execute --input SamplesTTbar/$$i --output Result/$$i; done
	hadd -f TTbar.root Result/*root

FullRunHistogramsHGG: Execute
	mkdir -p Result/
	rm -f Result/*root
	for i in `ls SamplesHGG/`; do echo $$i; ./Execute --input SamplesHGG/$$i --output Result/$$i; done
	hadd -f HGG.root Result/*root

FullRunHistogramsWLNu: Execute
	mkdir -p Result/
	rm -f Result/*root
	for i in `ls SamplesWLNu/`; do echo $$i; ./Execute --input SamplesWLNu/$$i --output Result/$$i; done
	hadd -f WLNu.root Result/*root

FullRunHistogramsVBFHInv: Execute
	mkdir -p Result/
	rm -f Result/*root
	for i in `ls SamplesVBFHInv/`; do echo $$i; ./Execute --input SamplesVBFHInv/$$i --output Result/$$i; done
	hadd -f VBFHInv.root Result/*root

FullRunHistograms: FullRunHistogramsHGG FullRunHistogramsTTbar FullRunHistogramsWLNu FullRunHistogramsVBFHInv

RunningMerge:
	hadd -k -f PartialMerge.root `ls Result/*root | sed '$$d'`

