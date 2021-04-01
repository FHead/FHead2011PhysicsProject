HTMLFile=~/public/html/L1Files.html

default: RunAll

Execute: MakeEfficiency.cpp
	CompileRootMacro MakeEfficiency.cpp Execute

RunAll: Execute
	# ./Execute --input DYLL.root              --output 001_STAMuon.pdf               --DoSTAMuon true
	# ./Execute --input DYLL.root              --output 002_STADisplacedMuon.pdf      --DoSTADisplacedMuon true
	# ./Execute --input DisplacedMuonPT2.root  --output 002_STADisplacedMuonPT2.pdf   --DoSTADisplacedMuon true
	# ./Execute --input DisplacedMuonPT10.root --output 002_STADisplacedMuonPT10.pdf  --DoSTADisplacedMuon true
	# ./Execute --input DisplacedMuonPT30.root --output 002_STADisplacedMuonPT30.pdf  --DoSTADisplacedMuon true
	./Execute --input DYLL.root              --output 003_TkMuon.pdf                --DoTkMuon true
	./Execute --input DYLL.root              --output 004_TkMuonStub.pdf            --DoTkMuonStub true
	./Execute --input DYLL.root              --output 004_TkMuonStubS12.pdf         --DoTkMuonStubS12 true
	# ./Execute --input HGG.root               --output 005_EGPhoton.pdf              --DoEG true
	# ./Execute --input DYLL.root              --output 006_EGElectron.pdf            --DoEGTrack true
	# ./Execute --input DYLL.root              --output 007_TkElectron.pdf            --DoElectron true
	# ./Execute --input DYLL.root              --output 008_TkIsoElectron.pdf         --DoIsoElectron true
	# ./Execute --input HGG.root               --output 009_TkIsoPhoton.pdf           --DoPhoton true
	# ./Execute --input HGG.root               --output 010_TkIsoPhotonPV.pdf         --DoPhotonPV true
	# ./Execute --input DYLL.root              --output 011_TkIsoElectronPV.pdf       --DoElectronPV true
	# ./Execute --input DYLL.root              --output 012_PuppiJet.pdf              --DoPuppiJet true
	# ./Execute --input TTbar.root             --output 012_PuppiJetTTbar.pdf         --DoPuppiJet true
	# ./Execute --input QCD.root               --output 012_PuppiJetMin25QCD.pdf      --DoPuppiJetMin25 true
	# ./Execute --input TTbar.root             --output 012_PuppiJetMin25TTbar.pdf    --DoPuppiJetMin25 true
	# ./Execute --input DYLL.root              --output 013_PuppiJetForMET.pdf        --DoPuppiJetForMET true
	# ./Execute --input TTbar.root             --output 013_PuppiJetForMETTTbar.pdf   --DoPuppiJetForMET true
	# ./Execute --input TTbar.root             --output 014_PuppiHT.pdf               --DoPuppiHT true
	# ./Execute --input VBFHInv.root           --output 015_PuppiMET.pdf              --DoPuppiMET true
	# ./Execute --input HTauTau.root           --output 016_PFTau.pdf                 --DoPFTau true
	# ./Execute --input HTauTau.root           --output 017_PFIsoTau.pdf              --DoPFIsoTau true
	# ./Execute --input TTbar.root             --output 018_CaloJet.pdf               --DoCaloJet true
	# ./Execute --input QCD.root               --output 018_CaloJetQCD.pdf            --DoCaloJet true
	# ./Execute --input TTbar.root             --output 019_CaloHT.pdf                --DoCaloHT true
	# ./Execute --input TTbar.root             --output 020_TrackerJet.pdf            --DoTrackerJet true
	# ./Execute --input TTbar.root             --output 021_TrackerHT.pdf             --DoTrackerHT true
	# ./Execute --input VBFHInv.root           --output 022_TrackerMET.pdf            --DoTrackerMET true
	# ./Execute --input HTauTau.root           --output 023_TkTau.pdf                 --DoTkTau true
	# ./Execute --input HTauTau.root           --output 024_CaloTkTau.pdf             --DoCaloTkTau true
	# ./Execute --input HTauTau.root           --output 025_TkEGTau.pdf               --DoTkEGTau true
	cp *.pdf ~/public/html/

GenerateHTML:
	bash GenerateHTML.sh > $(HTMLFile)

