default: TestRunHistograms 

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

TestRunHistograms: Execute
	./Execute --input ~cepeda/public/forYi/miniDYLL_v72.root \
		--output TestRunHistograms.root --config Default.config

PartialRunHistogramsDYLL: Execute
	mkdir -p Backup
	cp -f DYLL.root Backup/ || :
	ls SamplesDYLL/*MTD_633752_10* | tr '\n' ',' | sed "s/,$$//g" > DYLLPartial.txt
	./Execute --input `cat DYLLPartial.txt` --output DYLLPartial.root --StoredGen true --DoCharged false \
		--config Default.config

FullRunHistogramsDYLL: Execute
	mkdir -p Backup
	cp -f DYLL.root Backup/ || :
	ls SamplesDYLL/*MTD_633752_1* | tr '\n' ',' | sed "s/,$$//g" > DYLL1.txt
	ls SamplesDYLL/*MTD_633752_2* | tr '\n' ',' | sed "s/,$$//g" > DYLL2.txt
	ls SamplesDYLL/*MTD_633752_3* | tr '\n' ',' | sed "s/,$$//g" > DYLL3.txt
	ls SamplesDYLL/*MTD_633752_[04-9]* | tr '\n' ',' | sed "s/,$$//g" > DYLL4.txt
	./Execute --input `cat DYLL4.txt` --output DYLL4.root --StoredGen true --DoCharged false --config Default.config
	./Execute --input `cat DYLL3.txt` --output DYLL3.root --StoredGen true --DoCharged false --config Default.config
	./Execute --input `cat DYLL2.txt` --output DYLL2.root --StoredGen true --DoCharged false --config Default.config
	./Execute --input `cat DYLL1.txt` --output DYLL1.root --StoredGen true --DoCharged false --config Default.config
	hadd -f DYLL.root DYLL[1234].root

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

