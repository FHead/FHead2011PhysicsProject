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
	./Execute --input `ls SamplesTTbar/* | tr '\n' ',' | sed "s/,$$//g"` --output TTbar.root

FullRunHistogramsHGG: Execute
	cp HGG.root Backup/
	./Execute --input `ls SamplesHGGV1e/* | tr '\n' ',' | sed "s/,$$//g"` --output HGG.root

FullRunHistogramsWLNu: Execute
	cp WLNu.root Backup/
	./Execute --input `ls SamplesWLNu/* | tr '\n' ',' | sed "s/,$$//g"` --output WLNu.root

FullRunHistogramsVBFHInv: Execute
	./Execute --input `ls SamplesVBFHInv/* | tr '\n' ',' | sed "s/,$$//g"` --output VBFHInv.root

FullRunHistograms: FullRunHistogramsHGG FullRunHistogramsTTbar FullRunHistogramsWLNu FullRunHistogramsVBFHInv

RunningMerge:
	hadd -k -f PartialMerge.root `ls Result/*root | sed '$$d'`

