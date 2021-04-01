default: TestRun

Execute: MakeScalingPlot.cpp HelperFunctions.h
	CompileRootMacro MakeScalingPlot.cpp Execute

Export: ExportTextFile.cpp
	CompileRootMacro ExportTextFile.cpp Export

TestRun: Execute
	./Execute --input DYLL.root --output TestRunScalingPlots.pdf --curves TestRunScalingCurves.dh \
		--DoSTAMuon true --reference 0.95
	cp TestRunScalingPlots.pdf ~/public/html/

RunAll: Execute
	# ./Execute --input DYLL.root    --output 001_STAMuon.pdf           --curves Curves.dh \
	# 	--reference 0.95 --DoSTAMuon true
	# ./Execute --input DYLL.root    --output 002_STADisplacedMuon.pdf  --curves Curves.dh \
	# 	--reference 0.95 --DoSTADisplacedMuon true
	# ./Execute --input DYLL.root    --output 003_TkMuon.pdf            --curves Curves.dh \
	# 	--reference 0.95 --DoTkMuon true
	# ./Execute --input DYLL.root    --output 004_TkMuonStub.pdf        --curves Curves.dh \
	# 	--reference 0.95 --DoTkMuonStub true
	# ./Execute --input HGG.root     --output 005_EGPhoton.pdf          --curves Curves.dh \
	# 	--reference 0.95 --DoEG true
	# ./Execute --input DYLL.root    --output 006_EGElectron.pdf        --curves Curves.dh \
	# 	--reference 0.95 --DoEGTrack true
	# ./Execute --input DYLL.root    --output 007_TkElectron.pdf        --curves Curves.dh \
	# 	--reference 0.95 --DoElectron true
	# ./Execute --input DYLL.root    --output 008_TkIsoElectron.pdf     --curves Curves.dh \
	# 	--reference 0.95 --DoIsoElectron true
	# ./Execute --input HGG.root     --output 009_TkIsoPhoton.pdf       --curves Curves.dh \
	# 	--reference 0.95 --DoPhoton true
	# ./Execute --input HGG.root     --output 010_TkIsoPhotonPV.pdf     --curves Curves.dh \
	# 	--reference 0.95 --DoPhotonPV true
	# ./Execute --input DYLL.root    --output 011_TkIsoElectronPV.pdf   --curves Curves.dh \
	# 	--reference 0.95 --DoElectronPV true
	# ./Execute --input TTbar.root   --output 012_PuppiJet.pdf          --curves Curves.dh \
	# 	--reference 0.95 --DoPuppiJet true
	# ./Execute --input TTbar.root   --output 013_PuppiJetForMET.pdf    --curves Curves.dh \
	# 	--reference 0.95 --DoPuppiJetForMET true
	# ./Execute --input TTbar.root   --output 014_PuppiHT.pdf           --curves Curves.dh \
	# 	--reference 0.50 --DoPuppiHT true
	# ./Execute --input VBFHInv.root --output 015_PuppiMET.pdf          --curves Curves.dh \
	# 	--reference 0.50 --DoPuppiMET true
	# ./Execute --input HTauTau.root --output 016_PFTau.pdf             --curves Curves.dh \
	# 	--reference 0.50 --DoPFTau true
	# ./Execute --input HTauTau.root --output 017_PFIsoTau.pdf          --curves Curves.dh \
	# 	--reference 0.50 --DoPFIsoTau true
	# ./Execute --input DYLL.root    --output 018_CaloJet.pdf           --curves Curves.dh \
	# 	--reference 0.95 --DoCaloJet true
	# CaloHT is killed, we don't look at it
	# ./Execute --input DYLL.root    --output 019_CaloHT.pdf            --curves Curves.dh \
	# 	--reference 0.50 --DoCaloHT true
	# ./Execute --input TTbar.root   --output 020_TrackerJet.pdf        --curves Curves.dh \
	# 	--reference 0.95 --DoTrackerJet true
	# ./Execute --input TTbar.root   --output 021_TrackerHT.pdf         --curves Curves.dh \
	# 	--reference 0.50 --DoTrackerHT true
	# ./Execute --input VBFHInv.root --output 022_TrackerMET.pdf        --curves Curves.dh \
	# 	--reference 0.50 --DoTrackerMET true
	# ./Execute --input HTauTau.root --output 023_TkTau.pdf             --curves Curves.dh \
	# 	--reference 0.50 --DoTkTau true
	# ./Execute --input HTauTau.root --output 024_CaloTkTau.pdf         --curves Curves.dh \
	# 	--reference 0.50 --DoCaloTkTau true
	# ./Execute --input HTauTau.root --output 025_TkEGTau.pdf           --curves Curves.dh \
	# 	--reference 0.50 --DoTkEGTau true
	./Execute --input VBFHInv.root --output 026_TrackerMHT.pdf        --curves Curves.dh \
		--reference 0.50 --DoTrackerMHT true
	cp *.pdf ~/public/html/

RunExport: Export
	./Export

