default: TestRunHistograms 

Execute: FillHistograms.cpp Histograms.o
	CompileRootMacro FillHistograms.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`fastjet-config --cxxflags --libs` \
		Histograms.o

Histograms.o: Histograms.cpp
	CompileRootMacro Histograms.cpp Histograms.o -c

TestRunHistograms: Execute
	./Execute --input SamplesHTauTau/L1NtuplePhaseII_31.root --output TestRunHistograms.root

FullRunHistogramsTTbar: Execute
	mkdir -p Backup
	cp -f TTbar.root Backup/ || :
	./Execute --input `ls SamplesTTbar/* | tr '\n' ',' | sed "s/,$$//g"` --output TTbar.root --StoredGen true --DoCharged false

FullRunHistogramsTTbarRecluster: Execute
	mkdir -p Backup
	cp -f TTbarRecluster.root Backup/ || :
	./Execute --input `ls SamplesTTbar/* | tr '\n' ',' | sed "s/,$$//g"` --output TTbarRecluster.root --StoredGen false --DoCharged false

FullRunHistogramsHGG: Execute
	mkdir -p Backup
	cp -f HGG.root Backup/ || :
	./Execute --input `ls SamplesHGG/* | tr '\n' ',' | sed "s/,$$//g"` --output HGG.root

FullRunHistogramsWLNu: Execute
	mkdir -p Backup
	cp -f WLNu.root Backup/ || :
	./Execute --input `ls SamplesWLNu/* | tr '\n' ',' | sed "s/,$$//g"` --output WLNu.root

FullRunHistogramsWLNuPartial: Execute
	mkdir -p Backup
	cp -f WLNu.root Backup/ || :
	./Execute --input `ls SamplesWLNu/* | head -n10 | tr '\n' ',' | sed "s/,$$//g"` --output WLNu.root

FullRunHistogramsVBFHInv: Execute
	mkdir -p Backup
	cp -f VBFHInv.root Backup/ || :
	./Execute --input `ls SamplesVBFHInv/* | tr '\n' ',' | sed "s/,$$//g"` --output VBFHInv.root

FullRunHistogramsHH4B: Execute
	mkdir -p Backup
	cp HH4B.root Backup/ || :
	./Execute --input `ls SamplesHH4B/* | tr '\n' ',' | sed "s/,$$//g"` --output HH4B.root

FullRunHistogramsHTauTau: Execute
	mkdir -p Backup
	cp HTauTau.root Backup/ || :
	./Execute --input `ls SamplesHTauTau/* | tr '\n' ',' | sed "s/,$$//g"` --output HTauTau.root

FullRunHistogramsHTauTauV3p2: Execute
	mkdir -p Backup
	cp HTauTauV3p2.root Backup/ || :
	./Execute --input `ls SamplesHTauTauV3p2/* | tr '\n' ',' | sed "s/,$$//g"` --output HTauTauV3p2.root


FullRunHistograms: FullRunHistogramsHTauTau FullRunHistogramsTTbar FullRunHistogramsWLNu FullRunHistogramsVBFHInv

RunningMerge:
	hadd -k -f PartialMerge.root `ls Result/*root | sed '$$d'`

