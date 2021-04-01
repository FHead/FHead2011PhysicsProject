DYLLV11p3       = Outputs/DYLL_V11p3_20210208.root
VBFTauTauV11p3  = Outputs/VBFTauTau_V11p3_20210208.root
TTbarV11p3      = Outputs/TTbar_V11p3_20210208.root
FlatPhotonV11p3 = Outputs/FlatPhoton_V11p3_20210208.root
HGGV11p3        = Outputs/HGG_V11p3_20210208.root

Davignon      = true

default: V11p3IsoPlots

V11p3LDRPlots: Execute
	./Execute \
		--label "TkMuon","TkMuon (PT > 10)" \
		--file $(DYLLV11p3),$(DYLLV11p3) \
		--numerator "TkMuonLDR_DR_000000","TkMuonLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p3LDR_001.pdf
	./Execute \
		--label "STAMuon","STAMuon (PT > 10)" \
		--file $(DYLLV11p3),$(DYLLV11p3) \
		--numerator "StandaloneMuonLDR_DR_000000","StandaloneMuonLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p3LDR_002.pdf
	./Execute \
		--label "TkElectron","TkElectron (PT > 10)" \
		--file $(DYLLV11p3),$(DYLLV11p3) \
		--numerator "TkElectronTrackIDLDR_DR_000000","TkElectronTrackIDLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p3LDR_003.pdf
	./Execute \
		--label "EG (+electron)","EG (PT > 10)" \
		--file $(DYLLV11p3),$(DYLLV11p3) \
		--numerator "EGTrackIDLDR_DR_000000","EGTrackIDLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p3LDR_004.pdf
	./Execute \
		--label "EG (+photon)","EG (PT > 10)" \
		--file $(HGGV11p3),$(HGGV11p3) \
		--numerator "EGLDR_DR_000000","EGLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p3LDR_005.pdf
	./Execute \
		--label "TkPhoton","TkPhoton (PT > 10)" \
		--file $(HGGV11p3),$(HGGV11p3) \
		--numerator "TkPhotonTrackIDLDR_DR_000000","TkPhotonTrackIDLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p3LDR_006.pdf
	./Execute \
		--label "Phase1L1Jet","Phase1L1Jet (PT > 10)" \
		--file $(TTbarV11p3),$(TTbarV11p3) \
		--numerator "PFPhase1JetLDR_DR_000000","PFPhase1JetLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p3LDR_007.pdf
	./Execute \
		--label "NNTau","NNTau (PT > 10)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "NNTauLDR_DR_000000","NNTauLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p3LDR_008.pdf
	./Execute \
		--label "CaloTau","CaloTau (PT > 10)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "CaloTauLDR_DR_000000","CaloTauLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p3LDR_009.pdf
	cp V11p3LDR*pdf ~/public/html/

V11p3IsoPlots: Execute
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(HGGV11p3),$(HGGV11p3) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11p3Iso_001.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(HGGV11p3),$(HGGV11p3) \
		--numerator "TkPhotonPVTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonPVTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.10 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11p3Iso_002.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11p3Iso_001Flat.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkPhotonPVTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonPVTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.10 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11p3Iso_002Flat.pdf
	./Execute \
		--label "TkPhoton (Barrel; FlatPhoton V11)","TkPhoton (Barrel; HGG V11p3)" \
		--file $(FlatPhotonV11p3),$(HGGV11p3) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10Eta15_000000" \
		--denominator "simple","simple" \
		--title ";Isolation;a.u." --xmin 0 --xmax 0.35 --ymin 0.05 --ymax 150 --grid true \
		--Davignon $(Davignon) --legendx 0.25 --legendy 0.75 --line 0.00 --logy true --output V11p3Iso_003.pdf
	./Execute \
		--label "TkPhoton (Endcap; FlatPhoton V11)","TkPhoton (Endcap; HGG V11p3)" \
		--file $(FlatPhotonV11p3),$(HGGV11p3) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "simple","simple" \
		--title ";Isolation;a.u." --xmin 0 --xmax 0.35 --ymin 0.05 --ymax 150 --grid true \
		--Davignon $(Davignon) --legendx 0.25 --legendy 0.75 --line 0.00 --logy true --output V11p3Iso_004.pdf
	./Execute \
		--label "TkPhoton (PT > 10)","TkPhoton (PT > 20)","TkPhoton (PT > 40)" \
		--file $(HGGV11p3),$(HGGV11p3),$(HGGV11p3) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10_000000","TkPhotonTrackIDIso_TkIsoPT20_000000","TkPhotonTrackIDIso_TkIsoPT40_000000" \
		--denominator "simple","simple","simple" \
		--title ";Isolation;a.u." --xmin 0 --xmax 0.35 --ymin 0.05 --ymax 150 --grid true \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.65 --line 0.00 --logy true --output V11p3Iso_005.pdf
	./Execute \
		--label "TkPhoton (PT > 10)","TkPhoton (PT > 20)","TkPhoton (PT > 40)" \
		--file $(FlatPhotonV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10_000000","TkPhotonTrackIDIso_TkIsoPT20_000000","TkPhotonTrackIDIso_TkIsoPT40_000000" \
		--denominator "simple","simple","simple" \
		--title ";Isolation;a.u." --xmin 0 --xmax 0.35 --ymin 0.05 --ymax 150 --grid true \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.65 --line 0.00 --logy true --output V11p3Iso_005Flat.pdf
	./Execute \
		--label "TkElectron (Barrel)","TkElectron (Endcap)" \
		--file $(DYLLV11p3),$(DYLLV11p3) \
		--numerator "TkElectronIso_TkIsoPT10Eta15_000000","TkElectronIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.85 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.20 --line 0.982 --output V11p3Iso_006.pdf
	cp V11p3Iso*pdf ~/public/html/

V11p3TkMuonPlots: Execute
	./Execute \
		--label "TkMuon (p_{T} = 2-5 GeV)","TkMuon (p_{T} = 3-15 GeV)","TkMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "TkMuonIso_EtaPT2to5_000000","TkMuonIso_EtaPT3to15_000000","TkMuonIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_TkMuon_001.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "TkMuonIsoBEta_PT_000000","TkMuonIsoOEta_PT_000000","TkMuonIsoEEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p3_TkMuon_002.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "TkMuonIsoB_PT_000500","TkMuonIsoO_PT_000500","TkMuonIsoE_PT_000500" \
		--denominator "TkMuonIsoB_PT_000000","TkMuonIsoO_PT_000000","TkMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_TkMuon_003.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "TkMuonIsoB_PT_002000","TkMuonIsoO_PT_002000","TkMuonIsoE_PT_002000" \
		--denominator "TkMuonIsoB_PT_000000","TkMuonIsoO_PT_000000","TkMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_TkMuon_004.pdf
	./Execute \
		--label "TkMuon (region 1)","TkMuon (region 2)","TkMuon (region 3)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "TkMuonIsoB_EtaPT15_000000","TkMuonIsoO_EtaPT15_000000","TkMuonIsoE_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 15 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_TkMuon_005.pdf
	./Execute \
		--label "TkMuon (region 1)","TkMuon (region 2)","TkMuon (region 3)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "TkMuonIsoB_EtaPT3to15_000000","TkMuonIsoO_EtaPT3to15_000000","TkMuonIsoE_EtaPT3to15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 3-15 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_TkMuon_006.pdf
	cp V11p3_TkMuon_*pdf ~/public/html
	cp V11p3_TkMuon_*png ~/public/html

V11p3STAMuonPlots: Execute
	./Execute \
		--label "STAMuon (p_{T} = 2-5 GeV)","STAMuon (p_{T} = 3-15 GeV)","STAMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "StandaloneMuonIso_EtaPT2to5_000000","StandaloneMuonIso_EtaPT3to15_000000","StandaloneMuonIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_STAMuon_001.pdf
	./Execute \
		--label "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "StandaloneMuonIsoBEta_PT_000000","StandaloneMuonIsoOEta_PT_000000","StandaloneMuonIsoEEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p3_STAMuon_002.pdf
	./Execute \
		--label "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "StandaloneMuonIsoB_PT_000500","StandaloneMuonIsoO_PT_000500","StandaloneMuonIsoE_PT_000500" \
		--denominator "StandaloneMuonIsoB_PT_000000","StandaloneMuonIsoO_PT_000000","StandaloneMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_STAMuon_003.pdf
	./Execute \
		--label "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3) \
		--numerator "StandaloneMuonIsoB_PT_002000","StandaloneMuonIsoO_PT_002000","StandaloneMuonIsoE_PT_002000" \
		--denominator "StandaloneMuonIsoB_PT_000000","StandaloneMuonIsoO_PT_000000","StandaloneMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_STAMuon_004.pdf
	cp V11p3_STAMuon_*pdf ~/public/html
	cp V11p3_STAMuon_*png ~/public/html

V11p3PhotonPlots: Execute
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackIDWide_EtaPT25_000000","TkIsoPhotonPVTrackIDWide_EtaPT25_000000","TkIsoPhotonTrackIDWide_EtaPT25_000000","TkIsoPhotonPVTrackIDWide_EtaPT25_000000" \
		--denominator "TkPhotonTrackIDIsoWideNoMatch_EtaPT25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT25_000000" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_001.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackIDWide_EtaPT10to25_000000","TkIsoPhotonPVTrackIDWide_EtaPT10to25_000000","TkIsoPhotonTrackIDWide_EtaPT10to25_000000","TkIsoPhotonPVTrackIDWide_EtaPT10to25_000000" \
		--denominator "TkPhotonTrackIDIsoWideNoMatch_EtaPT10to25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT10to25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT10to25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT10to25_000000" \
		--title ";Gen. #eta;Matching efficiency (10 < p_{T} < 25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_002.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackIDWide_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackIDWide_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--denominator "TkPhotonTrackIDIsoWideNoMatch_PTEta15_000000","TkPhotonPVTrackIDIsoNoMatch_PTEta15_000000","TkPhotonTrackIDIsoWideNoMatch_PTEta15_000000","TkPhotonPVTrackIDIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_003.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackIDWide_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackIDWide_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000" \
		--denominator "TkPhotonTrackIDIsoWideNoMatch_PTEtaLarge_000000","TkPhotonPVTrackIDIsoNoMatch_PTEtaLarge_000000","TkPhotonTrackIDIsoWideNoMatch_PTEtaLarge_000000","TkPhotonPVTrackIDIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_004.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackID_PTEta15_001500","TkIsoPhotonPVTrackID_PTEta15_001500","TkIsoPhotonTrackID_PTEta15_001500","TkIsoPhotonPVTrackID_PTEta15_001500" \
		--denominator "TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_005.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackID_PTEta15_003000","TkIsoPhotonPVTrackID_PTEta15_003000","TkIsoPhotonTrackID_PTEta15_003000","TkIsoPhotonPVTrackID_PTEta15_003000" \
		--denominator "TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_006.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackID_PTEta15_005000","TkIsoPhotonPVTrackID_PTEta15_005000","TkIsoPhotonTrackID_PTEta15_005000","TkIsoPhotonPVTrackID_PTEta15_005000" \
		--denominator "TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 50 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_007.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackID_PTEtaLarge_001500","TkIsoPhotonPVTrackID_PTEtaLarge_001500","TkIsoPhotonTrackID_PTEtaLarge_001500","TkIsoPhotonPVTrackID_PTEtaLarge_001500" \
		--denominator "TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_008.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackID_PTEtaLarge_003000","TkIsoPhotonPVTrackID_PTEtaLarge_003000","TkIsoPhotonTrackID_PTEtaLarge_003000","TkIsoPhotonPVTrackID_PTEtaLarge_003000" \
		--denominator "TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_009.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p3),$(HGGV11p3),$(FlatPhotonV11p3),$(FlatPhotonV11p3) \
		--numerator "TkIsoPhotonTrackID_PTEtaLarge_005000","TkIsoPhotonPVTrackID_PTEtaLarge_005000","TkIsoPhotonTrackID_PTEtaLarge_005000","TkIsoPhotonPVTrackID_PTEtaLarge_005000" \
		--denominator "TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 50 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-3,-4 \
		--Davignon $(Davignon) --output V11p3_Photon_010.pdf
	cp V11p3_Photon_*pdf ~/public/html/

V11p3EGPlots: Execute
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDWideIso_EtaPT25_000000","TkElectronTrackIDWideIso_EtaPT25_000000","TkIsoElectronWide_EtaPT25_000000","TkIsoPhotonTrackIDWide_EtaPT25_000000" \
		--denominator "auto","auto","TkElectronIsoWideNoMatch_EtaPT25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT25_000000" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_001.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDWideIso_EtaPT10to25_000000","TkElectronTrackIDWideIso_EtaPT10to25_000000","TkIsoElectronWide_EtaPT10to25_000000","TkIsoPhotonTrackIDWide_EtaPT10to25_000000" \
		--denominator "auto","auto","TkElectronIsoWideNoMatch_EtaPT10to25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT10to25_000000" \
		--title ";Gen. #eta;Matching efficiency (10 < p_{T} < 25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_002.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--denominator "auto","auto","TkElectronIsoNoMatch_PTEta15_000000","TkPhotonTrackIDIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_003.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--denominator "auto","auto","TkElectronIsoNoMatch_PTEtaLarge_000000","TkPhotonTrackIDIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_004.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDIso_PTEta15_001500","TkElectronTrackIDIso_PTEta15_001500","TkIsoElectron_PTEta15_001500","TkIsoPhotonTrackID_PTEta15_001500" \
		--denominator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_005.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDIso_PTEta15_003000","TkElectronTrackIDIso_PTEta15_003000","TkIsoElectron_PTEta15_003000","TkIsoPhotonTrackID_PTEta15_003000" \
		--denominator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_006.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDIso_PTEta15_005000","TkElectronTrackIDIso_PTEta15_005000","TkIsoElectron_PTEta15_005000","TkIsoPhotonTrackID_PTEta15_005000" \
		--denominator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 50 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_007.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDIso_PTEtaLarge_001500","TkElectronTrackIDIso_PTEtaLarge_001500","TkIsoElectron_PTEtaLarge_001500","TkIsoPhotonTrackID_PTEtaLarge_001500" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_008.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDIso_PTEtaLarge_003000","TkElectronTrackIDIso_PTEtaLarge_003000","TkIsoElectron_PTEtaLarge_003000","TkIsoPhotonTrackID_PTEtaLarge_003000" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_009.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11p3),$(DYLLV11p3),$(DYLLV11p3),$(FlatPhotonV11p3) \
		--numerator "EGTrackIDIso_PTEtaLarge_005000","TkElectronTrackIDIso_PTEtaLarge_005000","TkIsoElectron_PTEtaLarge_005000","TkIsoPhotonTrackID_PTEtaLarge_005000" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 50 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11p3_EG_010.pdf
	cp V11p3_EG_*pdf ~/public/html/

V11p3JetPlots: Execute
	./Execute \
		--label "PuppiPhase1Jet (p_{T} = 40-100 GeV)","PuppiPhase1Jet (p_{T} > 100 GeV)" \
		--file $(TTbarV11p3),$(TTbarV11p3) \
		--numerator "PFPhase1JetWide_EtaPT40to100_000000","PFPhase1JetWide_EtaPT100_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -5 --xmax 5 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p3_Jet_001.pdf
	./Execute \
		--label "PuppiPhase1Jet (barrel)","PuppiPhase1Jet (endcap)","PuppiPhase1Jet (forward)" \
		--file $(TTbarV11p3),$(TTbarV11p3),$(TTbarV11p3) \
		--numerator "PFPhase1Jet_PTEta15_000000","PFPhase1Jet_PTEtaLarge_000000","PFPhase1JetForward_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p3_Jet_002.pdf
	./Execute \
		--label "PuppiPhase1Jet (barrel)","PuppiPhase1Jet (endcap)","PuppiPhase1Jet (forward)" \
		--file $(TTbarV11p3),$(TTbarV11p3),$(TTbarV11p3) \
		--numerator "PFPhase1Jet_PTEta15_005000","PFPhase1Jet_PTEtaLarge_005000","PFPhase1JetForward_PT_005000" \
		--denominator "PFPhase1Jet_PTEta15_000000","PFPhase1Jet_PTEtaLarge_000000","PFPhase1JetForward_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (p_{T} > 50 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p3_Jet_003.pdf
	./Execute \
		--label "PuppiPhase1Jet (barrel)","PuppiPhase1Jet (endcap)","PuppiPhase1Jet (forward)" \
		--file $(TTbarV11p3),$(TTbarV11p3),$(TTbarV11p3) \
		--numerator "PFPhase1Jet_PTEta15_012000","PFPhase1Jet_PTEtaLarge_012000","PFPhase1JetForward_PT_012000" \
		--denominator "PFPhase1Jet_PTEta15_000000","PFPhase1Jet_PTEtaLarge_000000","PFPhase1JetForward_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (p_{T} > 120 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p3_Jet_004.pdf
	cp V11p3_Jet_*pdf ~/public/html

V11p3HTMETPlots: Execute
	./Execute \
		--label "PuppiHT (200 GeV)","PuppiHT (350 GeV)" \
		--file $(TTbarV11p3),$(TTbarV11p3) \
		--numerator "PFPhase1HT_PT_020000","PFPhase1HT_PT_035000" \
		--denominator "PFPhase1HT_PT_000000","PFPhase1HT_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p3_HTMET_001.pdf
	./Execute \
		--label "PuppiMET (70 GeV)","PuppiMET (150 GeV)" \
		--file $(TTbarV11p3),$(TTbarV11p3) \
		--numerator "PuppiMET_PT_007000","PuppiMET_PT_015000" \
		--denominator "PuppiMET_PT_000000","PuppiMET_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p3_HTMET_002.pdf
	cp V11p3_HTMET*pdf ~/public/html/

V11p3TauPlots: Execute
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "NNTauLooseIso_EtaPT40_000000","NNTauIso_EtaPT40_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_Tau_001.pdf
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "NNTauLooseIso_EtaPT20to40_000000","NNTauIso_EtaPT20to40_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (20 < p_{T} < 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_Tau_002.pdf
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "NNTauLooseIso_PTEta15_000000","NNTauIso_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_Tau_003.pdf
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "NNTauLooseIso_PTEtaLarge_000000","NNTauIso_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_Tau_004.pdf
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "NNTauLooseIso_PTEta15_003000","NNTauIso_PTEta15_003000" \
		--denominator "NNTauLooseIso_PTEta15_000000","NNTauIso_PTEta15_000000" \
		--title ";Gen. #eta;Trigger efficiency (barrel, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_Tau_005.pdf
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "NNTauLooseIso_PTEta15_007000","NNTauIso_PTEta15_007000" \
		--denominator "NNTauLooseIso_PTEta15_000000","NNTauIso_PTEta15_000000" \
		--title ";Gen. #eta;Trigger efficiency (barrel, p_{T} > 70 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_Tau_006.pdf
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "NNTauLooseIso_PTEtaLarge_003000","NNTauIso_PTEtaLarge_003000" \
		--denominator "NNTauLooseIso_PTEtaLarge_000000","NNTauIso_PTEtaLarge_000000" \
		--title ";Gen. #eta;Trigger efficiency (endcap, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_Tau_007.pdf
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)" \
		--file $(VBFTauTauV11p3),$(VBFTauTauV11p3) \
		--numerator "NNTauLooseIso_PTEtaLarge_007000","NNTauIso_PTEtaLarge_007000" \
		--denominator "NNTauLooseIso_PTEtaLarge_000000","NNTauIso_PTEtaLarge_000000" \
		--title ";Gen. #eta;Trigger efficiency (endcap, p_{T} > 70 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p3_Tau_008.pdf
	cp V11p3_Tau_*pdf ~/public/html/


#####################################

V11TauNoCaloPlots: Execute
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_EtaPT40_000000","NNTauLooseIso_EtaPT40_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_001.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauDRIso_EtaPT40_000000","NNTauDRLooseIso_EtaPT40_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_001DR.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_EtaPT20to40_000000","NNTauLooseIso_EtaPT20to40_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (20 < p_{T} < 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_002.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauDRIso_EtaPT20to40_000000","NNTauDRLooseIso_EtaPT20to40_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (20 < p_{T} < 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_002DR.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_003.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauDRIso_PTEta15_000000","NNTauDRLooseIso_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_003DR.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_004.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauDRIso_PTEtaLarge_000000","NNTauDRLooseIso_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_004DR.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEta15_003000","NNTauLooseIso_PTEta15_003000" \
		--denominator "NNTauLooseIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000" \
		--title ";Gen. #eta;Trigger efficiency (barrel, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_005.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEta15_007000","NNTauLooseIso_PTEta15_007000" \
		--denominator "NNTauLooseIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000" \
		--title ";Gen. #eta;Trigger efficiency (barrel, p_{T} > 70 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_006.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEtaLarge_003000","NNTauLooseIso_PTEtaLarge_003000" \
		--denominator "NNTauLooseIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000" \
		--title ";Gen. #eta;Trigger efficiency (endcap, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_007.pdf
	./Execute \
		--label "NNTau (VBFHTauTau)","NNTau (HHbbTauTau)" \
		--file $(VBFHTauTauV11),$(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEtaLarge_007000","NNTauLooseIso_PTEtaLarge_007000" \
		--denominator "NNTauLooseIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000" \
		--title ";Gen. #eta;Trigger efficiency (endcap, p_{T} > 70 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -7,-4 \
		--Davignon $(Davignon) --output V11_Tau_008.pdf
	cp V11_Tau_*pdf ~/public/html/

V11TauPlots: Execute
	./Execute \
		--label "NNTau (Tight)","NNTau (Loose)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauIso_EtaPT40_000000","NNTauLooseIso_EtaPT40_000000","CaloTauIso_EtaPT40_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Tau_001.pdf
	./Execute \
		--label "NNTau (Tight)","NNTau (Loose)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauIso_EtaPT20to40_000000","NNTauLooseIso_EtaPT20to40_000000","CaloTauIso_EtaPT20to40_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (20 < p_{T} < 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Tau_002.pdf
	./Execute \
		--label "NNTau (Tight)","NNTau (Loose)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Tau_003.pdf
	./Execute \
		--label "NNTau (Tight)","NNTau (Loose)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Tau_004.pdf
	./Execute \
		--label "NNTau (Tight)","NNTau (Loose)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauIso_PTEta15_003000","NNTauLooseIso_PTEta15_003000","CaloTauIso_PTEta15_003000" \
		--denominator "NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--title ";Gen. #eta;Trigger efficiency (barrel, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Tau_005.pdf
	./Execute \
		--label "NNTau (Tight)","NNTau (Loose)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauIso_PTEta15_007000","NNTauLooseIso_PTEta15_007000","CaloTauIso_PTEta15_007000" \
		--denominator "NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--title ";Gen. #eta;Trigger efficiency (barrel, p_{T} > 70 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Tau_006.pdf
	./Execute \
		--label "NNTau (Tight)","NNTau (Loose)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauIso_PTEtaLarge_003000","NNTauLooseIso_PTEtaLarge_003000","CaloTauIso_PTEtaLarge_003000" \
		--denominator "NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--title ";Gen. #eta;Trigger efficiency (endcap, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Tau_007.pdf
	./Execute \
		--label "NNTau (Tight)","NNTau (Loose)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauIso_PTEtaLarge_007000","NNTauLooseIso_PTEtaLarge_007000","CaloTauIso_PTEtaLarge_007000" \
		--denominator "NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--title ";Gen. #eta;Trigger efficiency (endcap, p_{T} > 70 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Tau_008.pdf
	cp V11_Tau_*pdf ~/public/html/

Execute: PlotComparison.cpp
	CompileRootMacro PlotComparison.cpp Execute
