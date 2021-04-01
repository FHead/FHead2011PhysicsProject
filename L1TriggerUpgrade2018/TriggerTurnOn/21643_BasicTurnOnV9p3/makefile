Config = 20190823.config

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
	./Execute --input SamplesDarkPhoton/L1NtuplePhaseII_1.root \
		--output TestRunHistograms.root --config $(Config)

RunDYLL: Execute
	mkdir -p Backup
	cp -f DYLL.root Backup/ || :
	./Execute --input `ls SamplesDYLL/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` --output DYLL.root --StoredGen true --config $(Config)

RunDYLLV9: Execute
	mkdir -p Backup
	cp -f DYLLV9.root Backup/ || :
	./Execute --input `ls SamplesDYLLV9/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` --output DYLLV9.root --StoredGen true --config $(Config)

RunSingleTau: Execute
	mkdir -p Backup
	cp -f SingleTau.root Backup/ || :
	./Execute --input `ls SamplesSingleTau/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` --output SingleTau.root --StoredGen true --config $(Config)

RunDYLLPartial: Execute
	mkdir -p Backup
	cp -f DYLL.root Backup/ || :
	./Execute --input `ls SamplesDYLL/* | head -n 1000 | tr '\n' ',' | sed "s/,$$//g"` --output DYLL.root --StoredGen true --config $(Config)

RunHGG: Execute
	mkdir -p Backup
	cp -f HGG.root Backup/ || :
	./Execute --input `ls SamplesHGG/* | tr '\n' ',' | sed "s/,$$//g"` --output HGG.root --StoredGen true --config $(Config)

RunQCDPartial: Execute
	./Execute --input `ls SamplesQCD/* | head -n 25 | tr '\n' ',' | sed "s/,$$//g"` --output QCD.root --StoredGen true --config $(Config)

RunQCD: Execute
	mkdir -p Backup
	cp -f QCD.root Backup/ || :
	./Execute --input `ls SamplesQCD/* | tr '\n' ',' | sed "s/,$$//g"` --output QCD.root --StoredGen true --config $(Config)

RunTTbar: Execute
	mkdir -p Backup
	cp -f TTbar.root Backup/ || :
	./Execute --input `ls SamplesTTbar/* | tr '\n' ',' | sed "s/,$$//g"` --output TTbar.root --StoredGen true --config $(Config)

RunTTbarPartial: Execute
	mkdir -p Backup
	cp -f TTbar.root Backup/ || :
	./Execute --input `ls SamplesTTbar/* | head -n 100 | tr '\n' ',' | sed "s/,$$//g"` --output TTbar.root --StoredGen true --config $(Config)

RunVBFHInv: Execute
	mkdir -p Backup
	cp -f VBFHInv.root Backup/ || :
	./Execute --input `ls SamplesVBFHInv/* | tr '\n' ',' | sed "s/,$$//g"` --output VBFHInv.root --StoredGen true --config $(Config)

RunHTauTau: Execute
	mkdir -p Backup
	cp HTauTau.root Backup/ || :
	./Execute --input `ls SamplesHTauTau/* | tr '\n' ',' | sed "s/,$$//g"` --output HTauTau.root --StoredGen true --config $(Config)

RunHTauTauPartial: Execute
	mkdir -p Backup
	cp HTauTau.root Backup/ || :
	./Execute --input `ls SamplesHTauTau/* | head -n 5 | tr '\n' ',' | sed "s/,$$//g"` --output HTauTau.root --StoredGen true --config $(Config)

RunDisplacedMuon: Execute
	mkdir -p Backup
	cp DisplacedMuon*.root Backup/ || :
	./Execute --input `ls SamplesDisplacedMuonPT2/* | tr '\n' ',' | sed "s/,$$//g"` --output DisplacedMuonPT2.root --StoredGen true --config $(Config)
	./Execute --input `ls SamplesDisplacedMuonPT10/* | tr '\n' ',' | sed "s/,$$//g"` --output DisplacedMuonPT10.root --StoredGen true --config $(Config)
	./Execute --input `ls SamplesDisplacedMuonPT30/* | tr '\n' ',' | sed "s/,$$//g"` --output DisplacedMuonPT30.root --StoredGen true --config $(Config)

Run: RunHTauTau RunTTbar RunHGG RunVBFHInv RunDYLL

RunningMerge:
	hadd -k -f PartialMerge.root `ls Result/*root | sed '$$d'`

RunDisplacedMuonNew: Execute
	./Execute --input SamplesDisplacedMuon/L1NtuplePhaseII_1.root --output DisplacedMuon.root --config 20190404-muononly.config
