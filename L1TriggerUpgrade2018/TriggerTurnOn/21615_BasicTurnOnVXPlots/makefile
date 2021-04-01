default: V7V8V9PlotPart3

Execute: MakeScalingPlot.cpp HelperFunctions.h
	CompileRootMacro MakeScalingPlot.cpp Execute

ExecutePlot: V7V8V9Plots.cpp
	CompileRootMacro V7V8V9Plots.cpp ExecutePlot

Export: ExportTextFile.cpp
	CompileRootMacro ExportTextFile.cpp Export

V7V8V9CheckPart3: Execute
	./Execute --input DYLL_V7p52.root  --output V7_StandaloneMuon.pdf  --curves CurvesV7.dh \
		--reference 0.95 --DoSTAMuon true
	./Execute --input DYLL_V7p52.root  --output V7_TkMuon.pdf          --curves CurvesV7.dh \
		--reference 0.95 --DoTkMuon true
	./Execute --input DYLL_V8p2.root   --output V8_StandaloneMuon.pdf  --curves CurvesV8.dh \
		--reference 0.95 --DoSTAMuon true
	./Execute --input DYLL_V8p2.root   --output V8_TkMuon.pdf          --curves CurvesV8.dh \
		--reference 0.95 --DoTkMuon true
	./Execute --input DYLL_V9.root     --output V9_StandaloneMuon.pdf  --curves CurvesV9.dh \
		--reference 0.95 --DoSTAMuon true
	./Execute --input DYLL_V9.root     --output V9_TkMuon.pdf           --curves CurvesV9.dh \
		--reference 0.95 --DoTkMuon true

V7V8V9PlotPart3: ExecutePlot
	./ExecutePlot --State StandaloneMuonIsoB --OutputBase Scaling_StandaloneMuonIsoB \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State StandaloneMuonIsoO --OutputBase Scaling_StandaloneMuonIsoO \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State StandaloneMuonIsoE --OutputBase Scaling_StandaloneMuonIsoE \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State TkMuonB --OutputBase Scaling_TkMuonB \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State TkMuonO --OutputBase Scaling_TkMuonO \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State TkMuonE --OutputBase Scaling_TkMuonE \
		--MaxX 40 --MaxY 60
	cp Scaling_*pdf ~/public/html/


V7V8V9Check: Execute
	./Execute --input DYLL_V7p52.root  --output V7_EGElectron.pdf        --curves CurvesV7.dh \
		--reference 0.95 --DoEGTrack true
	./Execute --input DYLL_V7p52.root  --output V7_TkElectron.pdf        --curves CurvesV7.dh \
		--reference 0.95 --DoElectron true
	./Execute --input DYLL_V7p52.root  --output V7_TkIsoElectron.pdf     --curves CurvesV7.dh \
		--reference 0.95 --DoIsoElectron true
	./Execute --input DYLL_V8p2.root   --output V8_EGElectron.pdf        --curves CurvesV8.dh \
		--reference 0.95 --DoEGTrack true
	./Execute --input DYLL_V8p2.root   --output V8_TkElectron.pdf        --curves CurvesV8.dh \
		--reference 0.95 --DoElectron true
	./Execute --input DYLL_V8p2.root   --output V8_TkIsoElectron.pdf     --curves CurvesV8.dh \
		--reference 0.95 --DoIsoElectron true
	./Execute --input DYLL_V9.root     --output V9_EGElectron.pdf        --curves CurvesV9.dh \
		--reference 0.95 --DoEGTrack true
	./Execute --input DYLL_V9.root     --output V9_TkElectron.pdf        --curves CurvesV9.dh \
		--reference 0.95 --DoElectron true
	./Execute --input DYLL_V9.root     --output V9_TkIsoElectron.pdf     --curves CurvesV9.dh \
		--reference 0.95 --DoIsoElectron true

V7V8V9Plot: ExecutePlot
	./ExecutePlot --State EGTrackIDBarrel --OutputBase Scaling_EGTrackIDBarrel \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State EGTrackIDEndcap --OutputBase Scaling_EGTrackIDEndcap \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State EGTrackIDExtended --OutputBase Scaling_EGTrackIDExtended \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State TkElectronTrackIDBarrel --OutputBase Scaling_TkElectronTrackIDBarrel \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State TkElectronTrackIDEndcap --OutputBase Scaling_TkElectronTrackIDEndcap \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State TkIsoElectronBarrel --OutputBase Scaling_TkIsoElectronBarrel \
		--MaxX 40 --MaxY 60
	./ExecutePlot --State TkIsoElectronEndcap --OutputBase Scaling_TkIsoElectronEndcap \
		--MaxX 40 --MaxY 60
	cp Scaling_*pdf ~/public/html/

TestRun: Execute
	./Execute --input SingleTau.root --output 016_PFTau.pdf             --curves CurvesX.dh \
		--reference 0.50 --DoPFTau true
	./Execute --input SingleTau.root --output 017_PFIsoTau.pdf          --curves CurvesX.dh \
		--reference 0.50 --DoPFIsoTau true
	./Execute --input DYLL.root    --output 018_CaloJet.pdf           --curves CurvesX.dh \
		--reference 0.95 --DoCaloJet true
	./Execute --input DYLL.root   --output 012_PuppiJet.pdf          --curves CurvesX.dh \
		--reference 0.95 --DoPuppiJet true
	cp *.pdf ~/public/html/

RunAll: Execute
	# ./Execute --input DYLL.root    --output 001_STAMuon.pdf           --curves Curves.dh \
	# 	--reference 0.95 --DoSTAMuon true
	# ./Execute --input DYLL.root    --output 002_STADisplacedMuon.pdf  --curves Curves.dh \
	# 	--reference 0.95 --DoSTADisplacedMuon true
	# ./Execute --input DYLL.root    --output 003_TkMuon.pdf            --curves Curves.dh \
	# 	--reference 0.95 --DoTkMuon true
	# ./Execute --input DYLL.root    --output 004_TkMuonStub.pdf        --curves Curves.dh \
	# 	--reference 0.95 --DoTkMuonStub true
	# ./Execute --input DYLL.root    --output 004_TkMuonStubS12.pdf     --curves Curves.dh \
	# 	--reference 0.95 --DoTkMuonStubS12 true
	# ./Execute --input HGG.root     --output 005_EGPhoton.pdf          --curves Curves.dh \
	# 	--reference 0.95 --DoEG true
	./Execute --input DYLL.root    --output 006_EGElectron.pdf        --curves Curves.dh \
		--reference 0.95 --DoEGTrack true
	./Execute --input DYLL.root    --output 007_TkElectron.pdf        --curves Curves.dh \
		--reference 0.95 --DoElectron true
	./Execute --input DYLL.root    --output 008_TkIsoElectron.pdf     --curves Curves.dh \
		--reference 0.95 --DoIsoElectron true
	./Execute --input HGG.root     --output 009_TkIsoPhoton.pdf       --curves Curves.dh \
		--reference 0.95 --DoPhoton true
	# ./Execute --input HGG.root     --output 010_TkIsoPhotonPV.pdf     --curves Curves.dh \
	# 	--reference 0.95 --DoPhotonPV true
	# ./Execute --input DYLL.root    --output 011_TkIsoElectronPV.pdf   --curves Curves.dh \
	# 	--reference 0.95 --DoElectronPV true
	# ./Execute --input TTbar.root   --output 012_PuppiJet.pdf          --curves Curves.dh \
	# 	--reference 0.95 --DoPuppiJet true
	# ./Execute --input TTbar.root   --output 013_PuppiJetForMET.pdf    --curves Curves.dh \
	# 	--reference 0.95 --DoPuppiJetForMET true
	# ./Execute --input QCD.root     --output PuppiJetMin25.pdf         --curves Curves.dh \
	# 	--reference 0.95 --DoPuppiJetMin25 true
	# ./Execute --input TTbar.root   --output PuppiJetMin25TTbar.pdf    --curves Curves.dh \
	# 	--reference 0.95 --DoPuppiJetMin25 true --prefix TTbar
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
	# ./Execute --input VBFHInv.root --output 026_TrackerMHT.pdf        --curves Curves.dh \
	# 	--reference 0.50 --DoTrackerMHT true
	# ./Execute --input DYLL.root    --output 007_TkZElectron.pdf       --curves CurvesZ.dh \
	# 	--reference 0.95 --DoZElectron true
	# ./Execute --input HTauTau.root --output 027_NNTauLoose.pdf        --curves CurvesTemp.dh \
	# 	--reference 0.50 --DoNNTauLoose true
	# ./Execute --input HTauTau.root --output 028_NNTauTight.pdf        --curves CurvesTemp.dh \
	# 	--reference 0.50 --DoNNTauTight true
	# ./Execute --input HTauTau.root --output 029_CaloTau.pdf           --curves CurvesTemp.dh \
	# 	--reference 0.50 --DoCaloTau true
	cp *.pdf ~/public/html/

RunExport: Export
	./Export

