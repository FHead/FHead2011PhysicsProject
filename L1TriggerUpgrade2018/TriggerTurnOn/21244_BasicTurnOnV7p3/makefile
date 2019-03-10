Config = 20190304.config

default: RunTest 

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

RunTest: Execute
	./Execute --input SamplesDYLL/L1NtuplePhaseII_MTD_297.root \
		--output TestRunHistograms.root --config $(Config)

RunDYLL: Execute
	mkdir -p Backup
	cp -f DYLL.root Backup/ || :
	./Execute --input `ls SamplesDYLL/* | tr '\n' ',' | sed "s/,$$//g"` --output DYLL.root --StoredGen true --DoCharged false --config $(Config)

RunDYLLPartial: Execute
	mkdir -p Backup
	cp -f DYLL.root Backup/ || :
	./Execute --input `ls SamplesDYLL/* | head -n 200 | tr '\n' ',' | sed "s/,$$//g"` --output DYLL.root --StoredGen true --DoCharged false --config $(Config)

RunHGG: Execute
	mkdir -p Backup
	cp -f HGG.root Backup/ || :
	./Execute --input `ls SamplesHGG/* | tr '\n' ',' | sed "s/,$$//g"` --output HGG.root --StoredGen true --DoCharged false --config $(Config)

RunTTbar: Execute
	mkdir -p Backup
	cp -f TTbar.root Backup/ || :
	./Execute --input `ls SamplesTTbar/* | tr '\n' ',' | sed "s/,$$//g"` --output TTbar.root --StoredGen true --DoCharged false --config $(Config)

RunVBFHInv: Execute
	mkdir -p Backup
	cp -f VBFHInv.root Backup/ || :
	./Execute --input `ls SamplesVBFHInv/* | tr '\n' ',' | sed "s/,$$//g"` --output VBFHInv.root --StoredGen true --DoCharged false --config $(Config)

RunHTauTau: Execute
	mkdir -p Backup
	cp HTauTau.root Backup/ || :
	./Execute --input `ls SamplesHTauTau/* | tr '\n' ',' | sed "s/,$$//g"` --output HTauTau.root --StoredGen true --DoCharged false --config $(Config)

RunDisplacedMuon: Execute
	mkdir -p Backup
	cp DisplacedMuon*.root Backup/ || :
	./Execute --input `ls SamplesDisplacedMuonPT2/* | tr '\n' ',' | sed "s/,$$//g"` --output DisplacedMuonPT2.root --StoredGen true --DoCharged false --config $(Config)
	./Execute --input `ls SamplesDisplacedMuonPT10/* | tr '\n' ',' | sed "s/,$$//g"` --output DisplacedMuonPT10.root --StoredGen true --DoCharged false --config $(Config)
	./Execute --input `ls SamplesDisplacedMuonPT30/* | tr '\n' ',' | sed "s/,$$//g"` --output DisplacedMuonPT30.root --StoredGen true --DoCharged false --config $(Config)

Run: RunHTauTau RunTTbar RunHGG RunVBFHInv RunDYLL

RunningMerge:
	hadd -k -f PartialMerge.root `ls Result/*root | sed '$$d'`

