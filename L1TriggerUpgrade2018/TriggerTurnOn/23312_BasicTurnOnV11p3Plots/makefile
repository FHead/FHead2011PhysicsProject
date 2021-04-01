Davignon = true

DYLLV11p3      = Outputs/DYLL_V11p3_20210208.root
PhotonV11p3    = Outputs/FlatPhoton_V11p3_20210208.root
TTbarV11p3     = Outputs/TTbar_V11p3_20210208.root
VBFTauTauV11p3 = Outputs/VBFTauTau_V11p3_20210208.root
HGGV11p3       = Outputs/HGG_V11p3_20210208.root

default: RunV11p3Scaling

Debug: ExecutePlot
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "090NNTauLooseBarrel","090NNTauLooseEndcap" \
		--Labels "NNTau loose (barrel)","NNTau loose (endcap)" \
		--MaxX 80 --MaxY 300 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V11p3_TauLoose090

Execute: MakeScalingPlot.cpp HelperFunctions.h
	CompileRootMacro MakeScalingPlot.cpp Execute

ExecutePlot: V11Scaling.cpp
	CompileRootMacro V11Scaling.cpp ExecutePlot

Export: ExportTextFile.cpp
	CompileRootMacro ExportTextFile.cpp Export

RunV11p3: Execute
	./Execute --input $(DYLLV11p3)       --output V11p3_Fits_TkMuon.pdf            --curves CurvesV11p3.dh \
		--reference 0.95 --DoTkMuon true
	./Execute --input $(DYLLV11p3)       --output V11p3_Fits_STAMuon.pdf           --curves CurvesV11p3.dh \
		--reference 0.95 --DoSTAMuon true
	./Execute --input $(HGGV11p3)        --output V11p3_Fits_EGPhoton.pdf          --curves CurvesV11p3.dh \
		--reference 0.95 --DoEG true
	./Execute --input $(HGGV11p3)        --output V11p3_Fits_TkIsoPhoton.pdf       --curves CurvesV11p3.dh \
		--reference 0.95 --DoPhoton true
	./Execute --input $(HGGV11p3)        --output V11p3_Fits_TkIsoPhotonPV.pdf     --curves CurvesV11p3.dh \
		--reference 0.95 --DoPhotonPV true
	./Execute --input $(DYLLV11p3)       --output V11p3_Fits_EGElectron.pdf        --curves CurvesV11p3.dh \
		--reference 0.95 --DoEGTrack true
	./Execute --input $(DYLLV11p3)       --output V11p3_Fits_TkElectron.pdf        --curves CurvesV11p3.dh \
		--reference 0.95 --DoElectron true
	./Execute --input $(DYLLV11p3)       --output V11p3_Fits_TkIsoElectron.pdf     --curves CurvesV11p3.dh \
		--reference 0.95 --DoIsoElectron true
	./Execute --input $(TTbarV11p3)      --output V11p3_Fits_PFPhase1Jet.pdf       --curves CurvesV11p3.dh \
		--reference 0.95 --DoPFPhase1Jet true
	./Execute --input $(TTbarV11p3)      --output V11p3_Fits_PFPhase1HT.pdf        --curves CurvesV11p3.dh \
		--reference 0.50 --DoPFPhase1HT true
	./Execute --input $(TTbarV11p3)      --output V11p3_Fits_PFPhase1HT090.pdf     --curves CurvesV11p3.dh \
		--prefix 090 --reference 0.90 --DoPFPhase1HT true
	./Execute --input $(TTbarV11p3)      --output V11p3_Fits_PuppiMET.pdf          --curves CurvesV11p3.dh \
		--reference 0.50 --DoPuppiMET true
	./Execute --input $(TTbarV11p3)      --output V11p3_Fits_PuppiMET090.pdf       --curves CurvesV11p3.dh \
		--prefix 090 --reference 0.90 --DoPuppiMET true
	./Execute --input $(VBFTauTauV11p3)  --output V11p3_Fits_NNTau.pdf             --curves CurvesV11p3.dh \
		--reference 0.50 --DoNNTauTight true
	./Execute --input $(VBFTauTauV11p3)  --output V11p3_Fits_NNTauLoose.pdf        --curves CurvesV11p3.dh \
		--reference 0.50 --DoNNTauLoose true
	./Execute --input $(VBFTauTauV11p3)  --output V11p3_Fits_NNTau090.pdf          --curves CurvesV11p3.dh \
		--prefix 090 --reference 0.90 --DoNNTauTight true
	./Execute --input $(VBFTauTauV11p3)  --output V11p3_Fits_NNTauLoose090.pdf     --curves CurvesV11p3.dh \
		--prefix 090 --reference 0.90 --DoNNTauLoose true
	cp V11p3*pdf ~/public/html/

RunV11p2: Execute
	./Execute --input DYLL_V11p2.root    --output V11p2_Fits_TkMuonQual.pdf   --curves CurvesV11p2.dh \
		--reference 0.95 --DoTkMuonQual true

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

RunV11p2Scaling: ExecutePlot
	./ExecutePlot \
		--DHFiles "CurvesV11.dh","CurvesV11.dh","CurvesV11.dh","CurvesV11p2.dh","CurvesV11p2.dh","CurvesV11p2.dh" \
		--States "TkMuonB","TkMuonO","TkMuonE","TkMuonQualB","TkMuonQualO","TkMuonQualE" \
		--Labels "V11 barrel","V11 overlap","V11 endcap","V11.2 barrel","V11.2 overlap","V11.2 endcap" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p2_TkMuonQual

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

RunV11p3Scaling: ExecutePlot
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh","CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "EGTrackIDBarrel","TkElectronTrackIDBarrel","TkIsoElectronBarrel","TkIsoPhotonTrackIDBarrel" \
		--Labels "EG","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--MaxX 55 --MaxY 100 --Threshold "p_{T} (GeV) value at 95% efficiency" --Suffix " " \
		--Marker 20,21,22,23 \
		--Davignon $(Davignon) --OutputBase V11p3_EGBarrel
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh","CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "EGTrackIDEndcap","TkElectronTrackIDEndcap","TkIsoElectronEndcap","TkIsoPhotonTrackIDEndcap" \
		--Labels "EG","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--MaxX 55 --MaxY 100 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p3_EGEndcap
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "StandaloneMuonIsoB","TkMuonB" \
		--Labels "STA Muon","TkMuon" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p3_MuonBarrel
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "StandaloneMuonIsoO","TkMuonO" \
		--Labels "STA Muon","TkMuon" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p3_MuonOverlap
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "StandaloneMuonIsoE","TkMuonE" \
		--Labels "STA Muon","TkMuon" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p3_MuonEndcap
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "TkMuonB","TkMuonO","TkMuonE" \
		--Labels "TkMuon barrel","TkMuon overlap","TkMuon endcap" \
		--MaxX 40 --MaxY 60 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p3_TkMuon
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "NNTauTightBarrel","NNTauLooseBarrel" \
		--Labels "NNTau (Tight)","NNTau (Loose)" \
		--MaxX 80 --MaxY 250 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V11p3_TauBarrel
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "NNTauTightEndcap","NNTauLooseEndcap" \
		--Labels "NNTau (Tight)","NNTau (Loose)" \
		--MaxX 80 --MaxY 250 --Threshold "50%" \
		--Davignon $(Davignon) --OutputBase V11p3_TauEndcap
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "090NNTauTightBarrel","090NNTauLooseBarrel" \
		--Labels "NNTau (Tight)","NNTau (Loose)" \
		--MaxX 80 --MaxY 250 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V11p3_TauBarrel090
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "090NNTauTightEndcap","090NNTauLooseEndcap" \
		--Labels "NNTau (Tight)","NNTau (Loose)" \
		--MaxX 80 --MaxY 250 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V11p3_TauEndcap090
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "090NNTauLooseBarrel","090NNTauLooseEndcap" \
		--Labels "NNTau loose (barrel)","NNTau loose (endcap)" \
		--MaxX 80 --MaxY 250 --Threshold "90%" \
		--Davignon $(Davignon) --OutputBase V11p3_TauLoose090
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "PFPhase1JetBarrel","PFPhase1JetEndcap","PFPhase1JetForward"\
		--Labels "PuppiPhase1Jet (barrel)","PuppiPhase1Jet (endcap)","PuppiPhase1Jet (forward)" \
		--MaxX 200 --MaxY 450 --Threshold "95%" \
		--Davignon $(Davignon) --OutputBase V11p3_Jet
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "PFPhase1HT","090PFPhase1HT" \
		--Labels "PuppiPhase1HT (50%)","PuppiPhase1HT (90%)" \
		--MaxX 550 --MaxY 1000 --Threshold "Threshold location" \
		--Davignon $(Davignon) --OutputBase V11p3_HT
	./ExecutePlot \
		--DHFiles "CurvesV11p3.dh","CurvesV11p3.dh" \
		--States "PuppiMET","090PuppiMET" \
		--Labels "PuppiMET (50%)","PuppiMET (90%)" \
		--MaxX 200 --MaxY 450 --Threshold "Threshold location" \
		--Davignon $(Davignon) --OutputBase V11p3_MET
	cp V11p3*pdf ~/public/html

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
	cp ScalingsV11p3.txt ~/public/html

