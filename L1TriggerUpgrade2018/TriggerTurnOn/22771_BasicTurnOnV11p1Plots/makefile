Davignon = true

default: RunV11p1Scaling

Execute: MakeScalingPlot.cpp HelperFunctions.h
	CompileRootMacro MakeScalingPlot.cpp Execute

ExecutePlot: V11Scaling.cpp
	CompileRootMacro V11Scaling.cpp ExecutePlot

Export: ExportTextFile.cpp
	CompileRootMacro ExportTextFile.cpp Export

RunV11p1: Execute
	# ./Execute --input DYLL_V11p1.root    --output V11p1_Fits_TkMuon.pdf       --curves CurvesV11p1.dh \
	# 	--reference 0.95 --DoTkMuon true
	# ./Execute --input DYLL_V11p1.root    --output V11p1_Fits_TkMuonQual.pdf   --curves CurvesV11p1.dh \
	# 	--reference 0.95 --DoTkMuonQual true
	# ./Execute --input DYLL_V11p1.root    --output V11p1_Fits_STAMuon.pdf      --curves CurvesV11p1.dh \
	# 	--reference 0.95 --DoSTAMuon true
	# ./Execute --input DYLL_V11p1.root    --output V11p1_Fits_STAMuonQual.pdf  --curves CurvesV11p1.dh \
	# 	--reference 0.95 --DoSTAMuonQual true
	./Execute --input HGG_V11p1.root     --output V11p1_Fits_TkIsoPhoton.pdf  --curves CurvesV11p1.dh \
		--reference 0.95 --DoPhoton true
	./Execute --input HGG_V11p1.root     --output V11p1_Fits_TkIsoPhoton.pdf  --curves CurvesV11p1.dh \
		--reference 0.95 --DoPhotonPV true
	./Execute --input HHBBGG_V11p1.root  --output V11p1_Fits_TkIsoPhoton.pdf  --curves CurvesV11p1.dh \
		--prefix HH --reference 0.95 --DoPhoton true
	./Execute --input HHBBGG_V11p1.root  --output V11p1_Fits_TkIsoPhoton.pdf  --curves CurvesV11p1.dh \
		--prefix HH --reference 0.95 --DoPhotonPV true

RunV11: Execute
	# ./Execute --input DYLL_V11.root       --output V11_Fits_TkMuon.pdf            --curves CurvesV11.dh \
	# 	--reference 0.95 --DoTkMuon true
	# ./Execute --input Photon1_V11.root    --output V11_Fits_EGPhoton.pdf          --curves CurvesV11.dh \
	# 	--reference 0.95 --DoEG true
	# ./Execute --input Photon1_V11.root    --output V11_Fits_TkIsoPhoton.pdf       --curves CurvesV11.dh \
	# 	--reference 0.95 --DoPhoton true
	# ./Execute --input DYLL_V11.root       --output V11_Fits_EGElectron.pdf        --curves CurvesV11.dh \
	# 	--reference 0.95 --DoEGTrack true
	# ./Execute --input DYLL_V11.root       --output V11_Fits_TkElectron.pdf        --curves CurvesV11.dh \
	# 	--reference 0.95 --DoElectron true
	# ./Execute --input DYLL_V11.root       --output V11_Fits_TkIsoElectron.pdf     --curves CurvesV11.dh \
	# 	--reference 0.95 --DoIsoElectron true
	# ./Execute --input TTbar_V11.root      --output V11_Fits_PFPhase1Jet.pdf       --curves CurvesV11.dh \
	# 	--reference 0.95 --DoPFPhase1Jet true
	# ./Execute --input TTbar_V11.root      --output V11_Fits_PFPhase1HT.pdf        --curves CurvesV11.dh \
	# 	--reference 0.50 --DoPFPhase1HT true
	# ./Execute --input TTbar_V11.root      --output V11_Fits_PFPhase1HT090.pdf     --curves CurvesV11.dh \
	# 	--prefix 090 --reference 0.90 --DoPFPhase1HT true
	# ./Execute --input TTbar_V11.root      --output V11_Fits_PuppiMET.pdf          --curves CurvesV11.dh \
	# 	--reference 0.50 --DoPuppiMET true
	./Execute --input TTbar_V11.root      --output V11_Fits_PuppiMET.pdf          --curves CurvesV11.dh \
		--prefix 090 --reference 0.90 --DoPuppiMET true
	# ./Execute --input VBFHTauTau_V11.root --output V11_Fits_CaloTau.pdf           --curves CurvesV11.dh \
	# 	--reference 0.50 --DoCaloTau true
	# ./Execute --input VBFHTauTau_V11.root --output V11_Fits_NNTau.pdf             --curves CurvesV11.dh \
	# 	--reference 0.50 --DoNNTauTight true
	# ./Execute --input VBFHTauTau_V11.root --output V11_Fits_NNTauLoose.pdf        --curves CurvesV11.dh \
	# 	--reference 0.50 --DoNNTauLoose true
	# ./Execute --input VBFHTauTau_V11.root --output V11_Fits_NNTau090.pdf          --curves CurvesV11.dh \
	# 	--prefix 090 --reference 0.90 --DoNNTauTight true
	# ./Execute --input VBFHTauTau_V11.root --output V11_Fits_NNTauLoose090.pdf     --curves CurvesV11.dh \
	# 	--prefix 090 --reference 0.90 --DoNNTauLoose true
	# ./Execute --input HHbbTauTau_V11.root --output V11_Fits_HHNNTau.pdf           --curves CurvesV11.dh \
	# 	--prefix HH --reference 0.50 --DoNNTauTight true
	# ./Execute --input HHbbTauTau_V11.root --output V11_Fits_HHNNTauLoose.pdf      --curves CurvesV11.dh \
	# 	--prefix HH --reference 0.50 --DoNNTauLoose true
	# ./Execute --input HHbbTauTau_V11.root --output V11_Fits_HHNNTau090.pdf        --curves CurvesV11.dh \
	# 	--prefix 090HH --reference 0.90 --DoNNTauTight true
	# ./Execute --input HHbbTauTau_V11.root --output V11_Fits_HHNNTauLoose090.pdf   --curves CurvesV11.dh \
	# 	--prefix 090HH --reference 0.90 --DoNNTauLoose true
	cp V11*pdf ~/public/html/

RunV10: Execute
	./Execute --input DYLL_V10p7.root    --output V10_Fits_STAMuon.pdf           --curves CurvesV10.dh \
		--reference 0.95 --DoSTAMuon true
	# ./Execute --input DYLL_V10p7.root    --output V10_Fits_TkMuon.pdf            --curves CurvesV10.dh \
	# 	--reference 0.95 --DoTkMuon true
	# ./Execute --input DYLL_V10p7.root    --output V10_Fits_TkMuonStub.pdf        --curves CurvesV10.dh \
	# 	--reference 0.95 --DoTkMuonStub true
	# ./Execute --input HGG_V10p2.root     --output V10_Fits_EGPhoton.pdf          --curves CurvesV10.dh \
	# 	--reference 0.95 --DoEG true
	# ./Execute --input HGG_V10p2.root     --output V10_Fits_TkIsoPhoton.pdf       --curves CurvesV10.dh \
	# 	--reference 0.95 --DoPhoton true
	# ./Execute --input DYLL_V10p1.root    --output V10_Fits_EGElectron.pdf        --curves CurvesV10.dh \
	# 	--reference 0.95 --DoEGTrack true
	# ./Execute --input DYLL_V10p1.root    --output V10_Fits_TkElectron.pdf        --curves CurvesV10.dh \
	# 	--reference 0.95 --DoElectron true
	# ./Execute --input DYLL_V10p1.root    --output V10_Fits_TkIsoElectron.pdf     --curves CurvesV10.dh \
	# 	--reference 0.95 --DoIsoElectron true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_PFTau.pdf             --curves CurvesV10.dh \
	# 	--reference 0.50 --DoPFTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_PFIsoTau.pdf          --curves CurvesV10.dh \
	# 	--reference 0.50 --DoPFIsoTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_HPSTau.pdf            --curves CurvesV10.dh \
	# 	--reference 0.50 --DoHPSTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_HPSIsoTau.pdf         --curves CurvesV10.dh \
	# 	--reference 0.50 --DoHPSIsoTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_NNTau.pdf             --curves CurvesV10.dh \
	# 	--reference 0.50 --DoNNTauTight true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_NNTauLoose.pdf        --curves CurvesV10.dh \
	# 	--reference 0.50 --DoNNTauLoose true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_NNPFTau.pdf           --curves CurvesV10.dh \
	# 	--reference 0.50 --DoNNPFTauTight true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_NNPFTauLoose.pdf      --curves CurvesV10.dh \
	# 	--reference 0.50 --DoNNPFTauLoose true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_TkEGTau.pdf           --curves CurvesV10.dh \
	# 	--reference 0.50 --DoTkEGTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_CaloTkTau.pdf         --curves CurvesV10.dh \
	# 	--reference 0.50 --DoCaloTkTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_CaloTau.pdf           --curves CurvesV10.dh \
	# 	--reference 0.50 --DoCaloTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_PFTau.pdf             --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoPFTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_PFIsoTau.pdf          --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoPFIsoTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_HPSTau.pdf            --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoHPSTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_HPSIsoTau.pdf         --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoHPSIsoTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_NNTau.pdf             --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoNNTauTight true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_NNTauLoose.pdf        --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoNNTauLoose true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_NNPFTau.pdf           --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoNNPFTauTight true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_NNPFTauLoose.pdf      --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoNNPFTauLoose true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_TkEGTau.pdf           --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoTkEGTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_CaloTkTau.pdf         --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoCaloTkTau true
	# ./Execute --input HHbbTauTau_Tau_V10p5.root --output V10_Fits_CaloTau.pdf           --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoCaloTau true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_PuppiJet.pdf          --curves CurvesV10.dh \
	# 	--reference 0.95 --DoPuppiJet true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_PFPhase1Jet.pdf       --curves CurvesV10.dh \
	# 	--reference 0.95 --DoPFPhase1Jet true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_TrackerJet.pdf        --curves CurvesV10.dh \
	# 	--reference 0.95 --DoTrackerJet true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_CaloJet.pdf           --curves CurvesV10.dh \
	# 	--reference 0.95 --DoCaloJet true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_PuppiHT.pdf           --curves CurvesV10.dh \
	# 	--reference 0.50 --DoPuppiHT true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_PFPhase1HT.pdf        --curves CurvesV10.dh \
	# 	--reference 0.50 --DoPFPhase1HT true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_TrackerHT.pdf         --curves CurvesV10.dh \
	# 	--reference 0.50 --DoTrackerHT true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_CaloHT.pdf            --curves CurvesV10.dh \
	# 	--reference 0.50 --DoCaloHT true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_PuppiJet.pdf    --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.95 --DoPuppiJet true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_PFPhase1Jet.pdf --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.95 --DoPFPhase1Jet true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_TrackerJet.pdf  --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.95 --DoTrackerJet true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_CaloJet.pdf     --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.95 --DoCaloJet true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_PuppiHT.pdf     --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.50 --DoPuppiHT true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_PFPhase1HT.pdf  --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.50 --DoPFPhase1HT true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_TrackerHT.pdf   --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.50 --DoTrackerHT true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_CaloHT.pdf      --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.50 --DoCaloHT true
	# ./Execute --input HadronicTTbar_V10p3.root   --output V10_Fits_TTbar_PuppiHT.pdf     --curves CurvesV10.dh \
	# 	--prefix HadronicTTbar --reference 0.50 --DoPuppiHT true
	# ./Execute --input HadronicTTbar_V10p3.root   --output V10_Fits_TTbar_PFPhase1HT.pdf  --curves CurvesV10.dh \
	# 	--prefix HadronicTTbar --reference 0.50 --DoPFPhase1HT true
	# ./Execute --input HadronicTTbar_V10p3.root   --output V10_Fits_TTbar_TrackerHT.pdf   --curves CurvesV10.dh \
	# 	--prefix HadronicTTbar --reference 0.50 --DoTrackerHT true
	# ./Execute --input HadronicTTbar_V10p3.root   --output V10_Fits_TTbar_CaloHT.pdf      --curves CurvesV10.dh \
	# 	--prefix HadronicTTbar --reference 0.50 --DoCaloHT true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_PuppiHT.pdf           --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoPuppiHT true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_PFPhase1HT.pdf        --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoPFPhase1HT true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_TrackerHT.pdf         --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoTrackerHT true
	# ./Execute --input QCD_V10p3.root     --output V10_Fits_CaloHT.pdf            --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoCaloHT true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_PuppiHT.pdf     --curves CurvesV10.dh \
	# 	--prefix TTbar090 --reference 0.90 --DoPuppiHT true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_PFPhase1HT.pdf  --curves CurvesV10.dh \
	# 	--prefix TTbar090 --reference 0.90 --DoPFPhase1HT true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_TrackerHT.pdf   --curves CurvesV10.dh \
	# 	--prefix TTbar090 --reference 0.90 --DoTrackerHT true
	# ./Execute --input TTbar_V10p3.root   --output V10_Fits_TTbar_CaloHT.pdf      --curves CurvesV10.dh \
	# 	--prefix TTbar090 --reference 0.90 --DoCaloHT true
	# ./Execute --input HadronicTTbar_V10p3.root   --output V10_Fits_TTbar_PuppiHT.pdf     --curves CurvesV10.dh \
	# 	--prefix HadronicTTbar090 --reference 0.90 --DoPuppiHT true
	# ./Execute --input HadronicTTbar_V10p3.root   --output V10_Fits_TTbar_PFPhase1HT.pdf  --curves CurvesV10.dh \
	# 	--prefix HadronicTTbar090 --reference 0.90 --DoPFPhase1HT true
	# ./Execute --input HadronicTTbar_V10p3.root   --output V10_Fits_TTbar_TrackerHT.pdf   --curves CurvesV10.dh \
	# 	--prefix HadronicTTbar090 --reference 0.90 --DoTrackerHT true
	# ./Execute --input HadronicTTbar_V10p3.root   --output V10_Fits_TTbar_CaloHT.pdf      --curves CurvesV10.dh \
	# 	--prefix HadronicTTbar090 --reference 0.90 --DoCaloHT true
	# ./Execute --input VBFHInv_V10p3.root --output V10_Fits_PuppiMET.pdf          --curves CurvesV10.dh \
	# 	--reference 0.50 --DoPuppiMET true
	# ./Execute --input VBFHInv_V10p3.root --output V10_Fits_TrackerMET.pdf        --curves CurvesV10.dh \
	# 	--reference 0.50 --DoTrackerMET true
	# ./Execute --input TTbar_V10p3.root --output V10_Fits_PuppiMET.pdf          --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.50 --DoPuppiMET true
	# ./Execute --input TTbar_V10p3.root --output V10_Fits_TrackerMET.pdf        --curves CurvesV10.dh \
	# 	--prefix TTbar --reference 0.50 --DoTrackerMET true
	# ./Execute --input VBFHInv_V10p3.root --output V10_Fits_PuppiMET.pdf          --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoPuppiMET true
	# ./Execute --input VBFHInv_V10p3.root --output V10_Fits_TrackerMET.pdf        --curves CurvesV10.dh \
	# 	--prefix 090 --reference 0.90 --DoTrackerMET true
	# ./Execute --input TTbar_V10p3.root --output V10_Fits_PuppiMET.pdf          --curves CurvesV10.dh \
	# 	--prefix TTbar090 --reference 0.90 --DoPuppiMET true
	# ./Execute --input TTbar_V10p3.root --output V10_Fits_TrackerMET.pdf        --curves CurvesV10.dh \
	# 	--prefix TTbar090 --reference 0.90 --DoTrackerMET true
	cp *.pdf ~/public/html/

RunV10V11TauScaling: ExecutePlot
	./ExecutePlot \
		--DHFiles "CurvesV10.dh","CurvesV10.dh","CurvesV10.dh","CurvesV10.dh","CurvesV11.dh","CurvesV11.dh" \
		--States "NNTauTightBarrel","NNTauLooseBarrel","HNNTauTightBarrel","HNNTauLooseBarrel","NNTauTightBarrel","NNTauLooseBarrel" \
		--Labels "HHbbTauTau (Tight) V10.5","HHbbTauTau (Loose) V10.5","HTauTau (Tight) V10.5","HTauTau (Loose) V10.5","VBFHTauTau (Tight) V11","VBFHTauTau (Loose) V11" \
		--MaxX 80 --MaxY 150 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10V11_TauBarrelSamples
	./ExecutePlot \
		--DHFiles "CurvesV10.dh","CurvesV10.dh","CurvesV10.dh","CurvesV10.dh","CurvesV11.dh","CurvesV11.dh" \
		--States "NNTauTightEndcap","NNTauLooseEndcap","HNNTauTightEndcap","HNNTauLooseEndcap","NNTauTightEndcap","NNTauLooseEndcap" \
		--Labels "HHbbTauTau (Tight) V10.5","HHbbTauTau (Loose) V10.5","HTauTau (Tight) V10.5","HTauTau (Loose) V10.5","VBFHTauTau (Tight) V11","VBFHTauTau (Loose) V11" \
		--MaxX 80 --MaxY 150 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10V11_TauEndcapSamples
	cp V10V11*pdf ~/public/html/

RunV11p1Scaling: ExecutePlot
	./ExecutePlot \
		--DHFiles "CurvesV11p1.dh","CurvesV11p1.dh","CurvesV11p1.dh" \
		--States "TkMuonQualB","TkMuonQualO","TkMuonQualE" \
		--Labels "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p1_TkMuonQual
	./ExecutePlot \
		--DHFiles "CurvesV11p1.dh","CurvesV11p1.dh","CurvesV11p1.dh" \
		--States "StandaloneMuonQualIsoB","StandaloneMuonQualIsoO","StandaloneMuonQualIsoE" \
		--Labels "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p1_STAMuonQual
	./ExecutePlot \
		--DHFiles "CurvesV11.dh","CurvesV11p1.dh","CurvesV11p1.dh" \
		--States "TkMuonE","TkMuonE","TkMuonQualE" \
		--Labels "TkMuon (V11)","TkMuon (V11p1 - no quality)","TkMuon (V11p1 - with quality)" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p1_TkMuonE
	./ExecutePlot \
		--DHFiles "CurvesV11p1.dh","CurvesV11p1.dh" \
		--States "StandaloneMuonIsoE","StandaloneMuonQualIsoE" \
		--Labels "STAMuon (no quality)","STAMuon (with quality)" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p1_STAMuonE
	./ExecutePlot \
		--DHFiles "CurvesV11p1.dh","CurvesV11p1.dh","CurvesV11p1.dh","CurvesV11p1.dh" \
		--States "TkIsoPhotonTrackIDBarrel","TkIsoPhotonTrackIDEndcap","TkIsoPhotonPVTrackIDBarrel","TkIsoPhotonPVTrackIDEndcap" \
		--Labels "TkIsoPhoton (barrel)","TkIsoPhoton (endcap)","TkIsoPhotonPV (barrel)","TkIsoPhotonPV (endcap)" \
		--MaxX 40 --MaxY 70 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p1_Photon
	cp V11p1_* ~/public/html

RunV11Scaling: ExecutePlot
	./ExecutePlot \
		--States "EGTrackIDBarrel","TkElectronTrackIDBarrel","TkIsoElectronBarrel","TkIsoPhotonTrackIDBarrel" \
		--Labels "EG","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--MaxX 55 --MaxY 100 --Threshold "p_{T} (GeV) value at 95% efficiency" --Suffix " " \
		--Marker 20,21,22,23 \
		--Color -2,-3,-4,-5 \
		--Davignon $(Davignon) --OutputBase V11_EGBarrel
	./ExecutePlot \
		--States "EGTrackIDEndcap","TkElectronTrackIDEndcap","TkIsoElectronEndcap","TkIsoPhotonTrackIDEndcap" \
		--Labels "EG","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--MaxX 55 --MaxY 100 --Threshold "p_{T} (GeV) value at 95% efficiency" --Suffix " " \
		--Marker 20,21,22,23 \
		--Color -2,-3,-4,-5 \
		--Davignon $(Davignon) --OutputBase V11_EGEndcap
	./ExecutePlot \
		--States "TkMuonB","TkMuonO","TkMuonE" \
		--Labels "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11_Muon
	./ExecutePlot \
		--States "NNTauLooseBarrel","NNTauLooseEndcap","HHNNTauLooseBarrel","HHNNTauLooseEndcap" \
		--Labels "NNTau (barrel)","NNTau (endcap)","NNTau (barrel HH)","NNTau (endcap HH)" \
		--MaxX 80 --MaxY 150 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V11_Tau
	./ExecutePlot \
		--States "090NNTauLooseBarrel","090NNTauLooseEndcap" \
		--Labels "NNTau (barrel)","NNTau (endcap)" \
		--MaxX 80 --MaxY 200 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V11_Tau090
	./ExecutePlot \
		--States "PFPhase1JetBarrel","PFPhase1JetEndcap","PFPhase1JetForward" \
		--Labels "PFPhase1Jet (Barrel)","PFPhase1Jet (Endcap)","PFPhase1Jet (Forward)" \
		--MaxX 200 --MaxY 800 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11_Jet
	./ExecutePlot \
		--States "PFPhase1HT","090PFPhase1HT" \
		--Labels "PuppiPhase1HT (50%)","PuppiPhase1HT (90%)" \
		--MaxX 550 --MaxY 1000 --Threshold "Threshold" \
		--Davignon $(Davignon) --OutputBase V11_HT
	./ExecutePlot \
		--States "PuppiMET","090PuppiMET" \
		--Labels "PuppiMET (50%)","PuppiMET (90%)" \
		--MaxX 200 --MaxY 450 --Threshold "Threshold" \
		--Davignon $(Davignon) --OutputBase V11_MET
	cp V11*pdf ~/public/html

RunV10Scaling: ExecutePlot
	./ExecutePlot \
		--States "EGBarrel","EGTrackIDBarrel","TkElectronTrackIDBarrel","TkIsoElectronBarrel","TkIsoPhotonTrackIDBarrel" \
		--Labels "EGPhoton","EGElectron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--MaxX 55 --MaxY 100 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_EGBarrel
	./ExecutePlot \
		--States "EGTrackIDBarrel","TkElectronTrackIDBarrel","TkIsoElectronBarrel","TkIsoPhotonTrackIDBarrel" \
		--Labels "EG","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--MaxX 55 --MaxY 100 --Threshold "Barrel, 95%" \
		--Davignon $(Davignon) --OutputBase V10_EGBarrelNewYear
	./ExecutePlot \
		--States "EGTrackIDBarrel","TkElectronTrackIDBarrel","TkIsoElectronBarrel","TkIsoPhotonTrackIDBarrel" \
		--Labels "EG","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--MaxX 55 --MaxY 100 --Threshold "p_{T} (GeV) value at 95% efficiency" --Suffix " " \
		--Marker 20,21,22,23 \
		--Davignon $(Davignon) --OutputBase V10_EGBarrelNewYearV2
	./ExecutePlot \
		--States "EGEndcap","EGTrackIDEndcap","TkElectronTrackIDEndcap","TkIsoElectronEndcap","TkIsoPhotonTrackIDEndcap" \
		--Labels "EGPhoton","EGElectron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--MaxX 55 --MaxY 100 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_EGEndcap
	./ExecutePlot \
		--States "EGExtended","EGTrackIDExtended" \
		--Labels "EGPhoton","EGElectron" \
		--MaxX 55 --MaxY 100 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_EGOuter
	./ExecutePlot \
		--States "StandaloneMuonIsoB","TkMuonB","TkMuonStubB" \
		--Labels "STA Muon","TkMuon","TkMuonStub" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_MuonBarrel
	./ExecutePlot \
		--States "StandaloneMuonIsoO","TkMuonO","TkMuonStubO" \
		--Labels "STA Muon","TkMuon","TkMuonStub" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_MuonOverlap
	./ExecutePlot \
		--States "StandaloneMuonIsoE","TkMuonE","TkMuonStubE" \
		--Labels "STA Muon","TkMuon","TkMuonStub" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_MuonEndcap
	./ExecutePlot \
		--States "TkMuonStubExtended" \
		--Labels "TkMuonStub" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_MuonOuter
	./ExecutePlot \
		--States "NNTauTight","NNTauLoose","TkEGTau","CaloTau" \
		--Labels "NNTau (Tight)","NNTau (Loose)","tkEGTau","CaloTau" \
		--MaxX 80 --MaxY 150 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_Tau
	./ExecutePlot \
		--States "NNTauTightBarrel","NNTauLooseBarrel","TkEGTauBarrel","CaloTauBarrel" \
		--Labels "NNTau (Tight)","NNTau (Loose)","tkEGTau","CaloTau" \
		--MaxX 80 --MaxY 150 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_TauBarrel
	./ExecutePlot \
		--States "NNTauTightEndcap","NNTauLooseEndcap","TkEGTauEndcap","CaloTauEndcap" \
		--Labels "NNTau (Tight)","NNTau (Loose)","tkEGTau","CaloTau" \
		--MaxX 80 --MaxY 150 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_TauEndcap
	./ExecutePlot \
		--States "090NNTauTight","090NNTauLoose","090TkEGTau","090CaloTau" \
		--Labels "NNTau (Tight)","NNTau (Loose)","tkEGTau","CaloTau" \
		--MaxX 80 --MaxY 150 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_Tau090
	./ExecutePlot \
		--States "090NNTauTightBarrel","090NNTauLooseBarrel","090TkEGTauBarrel","090CaloTauBarrel" \
		--Labels "NNTau (Tight)","NNTau (Loose)","tkEGTau","CaloTau" \
		--MaxX 80 --MaxY 150 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_TauBarrel090
	./ExecutePlot \
		--States "090NNTauTightEndcap","090NNTauLooseEndcap","090TkEGTauEndcap","090CaloTauEndcap" \
		--Labels "NNTau (Tight)","NNTau (Loose)","tkEGTau","CaloTau" \
		--MaxX 80 --MaxY 150 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_TauEndcap090
	./ExecutePlot \
		--States "PFTau","PFIsoTau" \
		--Labels "HPSPFTau1","HPSPFTau1 (Medium)" \
		--MaxX 80 --MaxY 150 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_PFTau
	./ExecutePlot \
		--States "PFTauBarrel","PFIsoTauBarrel" \
		--Labels "HPSPFTau1","HPSPFTau1 (Medium)"\
		--MaxX 80 --MaxY 150 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_PFTauBarrel
	./ExecutePlot \
		--States "PFTauEndcap","PFIsoTauEndcap" \
		--Labels "HPSPFTau1","HPSPFTau1 (Medium)" \
		--MaxX 80 --MaxY 150 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_PFTauEndcap
	./ExecutePlot \
		--States "090PFTau","090PFIsoTau" \
		--Labels "HPSPFTau1","HPSPFTau1 (Medium)" \
		--MaxX 80 --MaxY 150 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_PFTau090
	./ExecutePlot \
		--States "090PFTauBarrel","090PFIsoTauBarrel" \
		--Labels "HPSPFTau1","HPSPFTau1 (Medium)"\
		--MaxX 80 --MaxY 150 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_PFTauBarrel090
	./ExecutePlot \
		--States "090PFTauEndcap","090PFIsoTauEndcap" \
		--Labels "HPSPFTau1","HPSPFTau1 (Medium)" \
		--MaxX 80 --MaxY 150 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_PFTauEndcap090
	./ExecutePlot \
		--States "PuppiJetBarrel","PFPhase1JetBarrel","TrackerJetBarrel","CaloJetBarrel" \
		--Labels "PuppiJet","PuppiPhase1Jet","TrackerJet","CaloJet" \
		--MaxX 200 --MaxY 800 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_JetBarrel
	./ExecutePlot \
		--States "PuppiJetEndcap","PFPhase1JetEndcap","TrackerJetEndcap","CaloJetEndcap" \
		--Labels "PuppiJet","PuppiPhase1Jet","TrackerJet","CaloJet" \
		--MaxX 200 --MaxY 800 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_JetEndcap
	./ExecutePlot \
		--States "PuppiJetForward","PFPhase1JetForward","TrackerJetForward","CaloJetForward" \
		--Labels "PuppiJet","PuppiPhase1Jet","TrackerJet","CaloJet" \
		--MaxX 200 --MaxY 800 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10_JetForward
	./ExecutePlot \
		--States "TTbarPuppiJetBarrel","TTbarPFPhase1JetBarrel","TTbarTrackerJetBarrel","TTbarCaloJetBarrel" \
		--Labels "PuppiJet","PuppiPhase1Jet","TrackerJet","CaloJet" \
		--MaxX 200 --MaxY 800 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10TTbar_JetBarrel
	./ExecutePlot \
		--States "TTbarPuppiJetEndcap","TTbarPFPhase1JetEndcap","TTbarTrackerJetEndcap","TTbarCaloJetEndcap" \
		--Labels "PuppiJet","PuppiPhase1Jet","TrackerJet","CaloJet" \
		--MaxX 200 --MaxY 800 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10TTbar_JetEndcap
	./ExecutePlot \
		--States "TTbarPuppiJetForward","TTbarPFPhase1JetForward","TTbarTrackerJetForward","TTbarCaloJetForward" \
		--Labels "PuppiJet","PuppiPhase1Jet","TrackerJet","CaloJet" \
		--MaxX 200 --MaxY 800 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V10TTbar_JetForward
	./ExecutePlot \
		--States "PuppiHT","PFPhase1HT","TrackerHT","CaloHT" \
		--Labels "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_HT
	./ExecutePlot \
		--States "TTbarPuppiHT","TTbarPFPhase1HT","TTbarTrackerHT","TTbarCaloHT" \
		--Labels "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10TTbar_HT
	./ExecutePlot \
		--States "HadronicTTbarPuppiHT","HadronicTTbarPFPhase1HT","HadronicTTbarTrackerHT","HadronicTTbarCaloHT" \
		--Labels "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10HadronicTTbar_HT
	./ExecutePlot \
		--States "090PuppiHT","090PFPhase1HT","090TrackerHT","090CaloHT" \
		--Labels "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_HT090
	./ExecutePlot \
		--States "TTbar090PuppiHT","TTbar090PFPhase1HT","TTbar090TrackerHT","TTbar090CaloHT" \
		--Labels "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10TTbar090_HT
	./ExecutePlot \
		--States "HadronicTTbar090PuppiHT","HadronicTTbar090PFPhase1HT","HadronicTTbar090TrackerHT","HadronicTTbar090CaloHT" \
		--Labels "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10HadronicTTbar090_HT
	./ExecutePlot \
		--States "PuppiHT","TrackerHT","CaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_HTNoPhase1HT
	./ExecutePlot \
		--States "TTbarPuppiHT""TTbarTrackerHT","TTbarCaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10TTbar_HTNoPhase1HT
	./ExecutePlot \
		--States "HadronicTTbarPuppiHT","HadronicTTbarTrackerHT","HadronicTTbarCaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10HadronicTTbar_HTNoPhase1HT
	./ExecutePlot \
		--States "090PuppiHT","090TrackerHT","090CaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_HT090NoPhase1HT
	./ExecutePlot \
		--States "TTbar090PuppiHT","TTbar090TrackerHT","TTbar090CaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10TTbar090_HTNoPhase1HT
	./ExecutePlot \
		--States "HadronicTTbar090PuppiHT","HadronicTTbar090TrackerHT","HadronicTTbar090CaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10HadronicTTbar090_HTNoPhase1HT
	./ExecutePlot \
		--States "PFPhase1HT","TrackerHT","CaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_HTYesPhase1HT
	./ExecutePlot \
		--States "TTbarPFPhase1HT""TTbarTrackerHT","TTbarCaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10TTbar_HTYesPhase1HT
	./ExecutePlot \
		--States "HadronicTTbarPFPhase1HT","HadronicTTbarTrackerHT","HadronicTTbarCaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10HadronicTTbar_HTYesPhase1HT
	./ExecutePlot \
		--States "090PFPhase1HT","090TrackerHT","090CaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_HT090YesPhase1HT
	./ExecutePlot \
		--States "TTbar090PFPhase1HT","TTbar090TrackerHT","TTbar090CaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10TTbar090_HTYesPhase1HT
	./ExecutePlot \
		--States "HadronicTTbar090PFPhase1HT","HadronicTTbar090TrackerHT","HadronicTTbar090CaloHT" \
		--Labels "PuppiHT","TrackerHT","CaloHT" \
		--MaxX 550 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10HadronicTTbar090_HTYesPhase1HT
	./ExecutePlot \
		--States "PuppiMET","TrackerMET" \
		--Labels "PuppiMET","TrackerMET" \
		--MaxX 200 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10_MET
	./ExecutePlot \
		--States "TTbarPuppiMET","TTbarTrackerMET" \
		--Labels "PuppiMET","TrackerMET" \
		--MaxX 200 --MaxY 1000 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V10TTbar_MET
	./ExecutePlot \
		--States "090PuppiMET","090TrackerMET" \
		--Labels "PuppiMET","TrackerMET" \
		--MaxX 200 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10_MET090
	./ExecutePlot \
		--States "TTbar090PuppiMET","TTbar090TrackerMET" \
		--Labels "PuppiMET","TrackerMET" \
		--MaxX 200 --MaxY 1000 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V10TTbar_MET090
	cp V10*pdf ~/public/html

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
	cp ScalingsV11.txt ~/public/html

