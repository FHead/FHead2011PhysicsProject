Config     = 20200213.config
MuEGConfig = 20191212MuEG.config
MuConfig   = 20191212Mu.config
TauConfig  = 20200308Tau.config
HadConfig  = 20191022Hadronic.config

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
	./Execute --input `ls SamplesDYLL/* | head -n 100 | tr '\n' ',' | sed "s/,$$//g"` \
		--output TestRun.root --StoredGen true --config $(Config)

RunLDR: Execute
	# ./Execute --input `ls SamplesDYLL/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output DYLLLDR.root --StoredGen true --config $(Config) --LDROnly true
	# ./Execute --input `ls SamplesHTauTau/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output HTauTauLDR.root --StoredGen true --config $(Config) --LDROnly true
	# ./Execute --input `ls SamplesHGG/* | tr '\n' ',' | sed "s/,$$//g"` --output HGGLDR.root --StoredGen true --config $(Config) --LDROnly true
	./Execute --input `ls SamplesQCD/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output QCDLDR.root --StoredGen true --config $(Config) --LDROnly true
	./Execute --input `ls SamplesTTbar/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output TTbarLDR.root --StoredGen true --config $(Config) --LDROnly true

RunMuEGTau: Execute
	# ./Execute --input `ls SamplesDYLL/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output DYLLMuEG.root --StoredGen true --config $(MuEGConfig)
	# ./Execute --input `ls SamplesHGG/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output HGGMuEG.root --StoredGen true --config $(MuEGConfig)
	# ./Execute --input `ls SamplesHTauTau/* | tr '\n' ',' | sed "s/,$$//g"` --output HTauTauTau.root --StoredGen true --config $(TauConfig)
	./Execute --input `ls SamplesHHbbTauTau/* | tr '\n' ',' | sed "s/,$$//g"` --output HHbbTauTauTau.root --StoredGen true --config $(TauConfig)
	# ./Execute --input `ls SamplesDarkPhoton/* | grep root$ | tr '\n' ',' | sed "s/,$$//g"` --output DarkPhotonMuEG.root --StoredGen true --config $(MuEGConfig)
	# ./Execute --input `ls SamplesDarkSUSYCT1/* | grep root$ | tr '\n' ',' | sed "s/,$$//g"` --output DarkSUSYCT1MuEG.root --StoredGen true --config $(MuConfig)
	# ./Execute --input `ls SamplesDarkSUSYCT10/* | grep root$ | tr '\n' ',' | sed "s/,$$//g"` --output DarkSUSYCT10MuEG.root --StoredGen true --config $(MuConfig)
	# ./Execute --input `ls SamplesDarkSUSYCT100/* | grep root$ | tr '\n' ',' | sed "s/,$$//g"` --output DarkSUSYCT100MuEG.root --StoredGen true --config $(MuConfig)
	# ./Execute --input `ls SamplesDarkSUSYCT1000/* | grep root$ | tr '\n' ',' | sed "s/,$$//g"` --output DarkSUSYCT1000MuEG.root --StoredGen true --config $(MuConfig)
	# ./Execute --input `ls SamplesDarkSUSYCT10k/* | grep root$ | tr '\n' ',' | sed "s/,$$//g"` --output DarkSUSYCT10kMuEG.root --StoredGen true --config $(MuConfig)
	# ./Execute --input `ls SamplesDisplacedMuon/* | grep root$ | tr '\n' ',' | sed "s/,$$//g"` --output DisplacedMuon.root --StoredGen true --config $(MuConfig)

RunHadronic: Execute
	# ./Execute --input `ls SamplesQCD/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output QCDHadronic.root --StoredGen true --config $(HadConfig)
	./Execute --input `ls SamplesTTbar/* | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/TTbarHadronic.root --StoredGen true --config $(HadConfig)
	# ./Execute --input `ls SamplesVBFHInv/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output VBFHInvHadronic.root --StoredGen true --config $(HadConfig)

RunDYLL: Execute
	./Execute --input `ls SamplesDYLL/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/DYLL.root --StoredGen true --config $(Config)

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
	./Execute --input `ls SamplesQCD/* | head -n 200 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/QCDPartial.root --StoredGen true --config $(Config)

RunQCD: Execute
	mkdir -p Backup
	cp -f QCD.root Backup/ || :
	./Execute --input `ls SamplesQCD/* | tr '\n' ',' | sed "s/,$$//g"` --output QCD.root --StoredGen true --config $(Config)

RunQCDSeparate: Execute
	mkdir -p Backup
	cp -f QCD.root Backup/ || :
	./Execute --input `ls SamplesQCD/* | head -n 400 | tail -n 200 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/QCD2.root --StoredGen true --config $(Config) &
	./Execute --input `ls SamplesQCD/* | head -n 600 | tail -n 200 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/QCD3.root --StoredGen true --config $(Config) &
	./Execute --input `ls SamplesQCD/* | head -n 800 | tail -n 200 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/QCD4.root --StoredGen true --config $(Config) &
	./Execute --input `ls SamplesQCD/* | head -n 1000 | tail -n 200 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/QCD5.root --StoredGen true --config $(Config) &
	./Execute --input `ls SamplesQCD/* | head -n 1200 | tail -n 200 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/QCD6.root --StoredGen true --config $(Config) &
	./Execute --input `ls SamplesQCD/* | head -n 1400 | tail -n 200 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/QCD7.root --StoredGen true --config $(Config) &
	./Execute --input `ls SamplesQCD/* | head -n 1596 | tail -n 196 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/QCD8.root --StoredGen true --config $(Config) &

RunTTbar: Execute
	mkdir -p Backup
	cp -f TTbar.root Backup/ || :
	./Execute --input `ls SamplesTTbar/* | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/TTbar.root --StoredGen true --config $(Config)

RunHadronicTTbar: Execute
	mkdir -p Backup
	cp -f HadronicTTbar.root Backup/ || :
	./Execute --input `ls SamplesTTbar/* | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/HadronicTTbar.root --StoredGen true --config $(Config) --RejectLeptonicW true

RunTTbarPartial: Execute
	mkdir -p Backup
	cp -f TTbar.root Backup/ || :
	./Execute --input `ls SamplesTTbar/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output TTbar.root --StoredGen true --config $(Config)

RunHadronicTTbarPartial: Execute
	mkdir -p Backup
	cp -f HadronicTTbar.root Backup/ || :
	./Execute --input `ls SamplesTTbar/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output HadronicTTbar.root --StoredGen true --config $(Config) --RejectLeptonicW true

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
