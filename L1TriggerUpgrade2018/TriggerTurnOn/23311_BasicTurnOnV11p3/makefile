Config     = 20210208.config
EGConfig   = 20200930EG.config
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
	./Execute --input `ls SamplesTTbar/* | head -n 10 | tr '\n' ',' | sed "s/,$$//g"` \
		--output TestRun.root --StoredGen true --config $(Config)

RunLDR: Execute
	./Execute --input `ls SamplesDYLL/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output DYLLLDR.root --StoredGen true --config $(Config) --LDROnly true
	./Execute --input `ls SamplesHGG/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output HGGLDR.root --StoredGen true --config $(Config) --LDROnly true
	./Execute --input `ls SamplesFlatPhoton/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output FlatPhotonLDR.root --StoredGen true --config $(Config) --LDROnly true
	./Execute --input `ls SamplesTTbar/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output TTbarLDR.root --StoredGen true --config $(Config) --LDROnly true
	./Execute --input `ls SamplesVBFTauTau/* | head -n 40 | tr '\n' ',' | sed "s/,$$//g"` --output VBFTauTauLDR.root --StoredGen true --config $(Config) --LDROnly true

RunDYLL: Execute
	./Execute --input `ls SamplesDYLL/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/DYLL.root --StoredGen true --config $(Config)

RunHGG: Execute
	./Execute --input `ls SamplesHGG/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/HGG.root --StoredGen true --config $(Config)

RunPhoton: Execute
	./Execute --input `ls SamplesFlatPhoton/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/FlatPhoton.root --StoredGen true --config $(Config)

RunTTbar: Execute
	./Execute --input `ls SamplesTTbar/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/TTbar.root --StoredGen true --config $(Config)

RunVBFTauTau: Execute
	./Execute --input `ls SamplesVBFTauTau/* | head -n 10000 | tr '\n' ',' | sed "s/,$$//g"` --output /tmp/chenyi/VBFTauTau.root --StoredGen true --config $(Config)


