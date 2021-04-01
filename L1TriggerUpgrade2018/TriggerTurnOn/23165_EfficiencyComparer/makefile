DYLLV11       = DYLLV11.root
DYLLV11p1     = DYLLV11p1.root
DYLLV11p2     = DYLLV11p2.root
VBFHTauTauV11 = VBFHTauTauV11.root
HHbbTauTauV11 = HHbbTauTauV11.root
TTbarV11      = TTbarV11.root
Photon1V11    = Photon1V11.root
Photon2V11    = Photon2V11.root
HGGV11p1      = HGGV11p1.root
HHBBGGV11p1   = HHBBGGV11p1.root
FlatPhotonV11 = FlatPhotonV11.root

Davignon      = true

# default: V11p1TkMuonPlots V11p1STAMuonPlots
default: V11p1PhotonPlots

V11p1LDRPlots: Execute
	./Execute \
		--label "TkMuon","TkMuon (PT > 10)" \
		--file $(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonLDR_DR_000000","TkMuonLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p1LDR_001.pdf
	./Execute \
		--label "STAMuon","STAMuon (PT > 10)" \
		--file $(DYLLV11p1),$(DYLLV11p1) \
		--numerator "StandaloneMuonLDR_DR_000000","StandaloneMuonLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p1LDR_002.pdf
	./Execute \
		--label "TkPhoton","TkPhoton (PT > 10)" \
		--file $(HGGV11p1),$(HGGV11p1) \
		--numerator "TkPhotonTrackIDLDR_DR_000000","TkPhotonTrackIDLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11p1LDR_003.pdf
	cp V11p1LDR*pdf ~/public/html/

V11p1IsoPlots: Execute
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(HGGV11p1),$(HGGV11p1) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11p1Iso_001.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(HGGV11p1),$(HGGV11p1) \
		--numerator "TkPhotonPVTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonPVTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.10 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11p1Iso_002.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11p1Iso_001Flat.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkPhotonPVTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonPVTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.10 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11p1Iso_002Flat.pdf
	./Execute \
		--label "TkPhoton (Barrel; FlatPhoton V11)","TkPhoton (Barrel; HGG V11p1)" \
		--file $(FlatPhotonV11),$(HGGV11p1) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10Eta15_000000" \
		--denominator "simple","simple" \
		--title ";Isolation;a.u." --xmin 0 --xmax 0.35 --ymin 0.05 --ymax 150 --grid true \
		--Davignon $(Davignon) --legendx 0.25 --legendy 0.75 --line 0.00 --logy true --output V11p1Iso_003.pdf
	./Execute \
		--label "TkPhoton (Endcap; FlatPhoton V11)","TkPhoton (Endcap; HGG V11p1)" \
		--file $(FlatPhotonV11),$(HGGV11p1) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "simple","simple" \
		--title ";Isolation;a.u." --xmin 0 --xmax 0.35 --ymin 0.05 --ymax 150 --grid true \
		--Davignon $(Davignon) --legendx 0.25 --legendy 0.75 --line 0.00 --logy true --output V11p1Iso_004.pdf
	./Execute \
		--label "TkPhoton (PT > 10)","TkPhoton (PT > 20)","TkPhoton (PT > 40)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HGGV11p1) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10_000000","TkPhotonTrackIDIso_TkIsoPT20_000000","TkPhotonTrackIDIso_TkIsoPT40_000000" \
		--denominator "simple","simple","simple" \
		--title ";Isolation;a.u." --xmin 0 --xmax 0.35 --ymin 0.05 --ymax 150 --grid true \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.65 --line 0.00 --logy true --output V11p1Iso_005.pdf
	./Execute \
		--label "TkPhoton (PT > 10)","TkPhoton (PT > 20)","TkPhoton (PT > 40)" \
		--file $(FlatPhotonV11),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10_000000","TkPhotonTrackIDIso_TkIsoPT20_000000","TkPhotonTrackIDIso_TkIsoPT40_000000" \
		--denominator "simple","simple","simple" \
		--title ";Isolation;a.u." --xmin 0 --xmax 0.35 --ymin 0.05 --ymax 150 --grid true \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.65 --line 0.00 --logy true --output V11p1Iso_005Flat.pdf
	cp V11p1Iso*pdf ~/public/html/

V11p1TkMuonEfficiencyCheckPlots: Execute
	./Execute \
		--label "TkMuon (p_{T} = 2-5 GeV)","TkMuon (p_{T} = 3-15 GeV)","TkMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonQualIsoEffCheck1_EtaPT2to5_000000","TkMuonQualIsoEffCheck1_EtaPT3to15_000000","TkMuonQualIsoEffCheck1_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuonEfficiencyCheck_001.pdf
	./Execute \
		--label "TkMuon (p_{T} = 2-5 GeV)","TkMuon (p_{T} = 3-15 GeV)","TkMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonQualIsoEffCheck2_EtaPT2to5_000000","TkMuonQualIsoEffCheck2_EtaPT3to15_000000","TkMuonQualIsoEffCheck2_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuonEfficiencyCheck_002.pdf
	cp V11p1_TkMuonEfficiencyCheck*pdf ~/public/html/

V11p2TkMuonExtraPlots: Execute
	./Execute \
		--label "V11 TkMuon (p_{T} = 2-5 GeV)","V11 TkMuon (p_{T} = 3-15 GeV)","V11 TkMuon (p_{T} > 15 GeV)","V11.2 TkMuon (p_{T} = 2-5 GeV)","V11.2 TkMuon (p_{T} = 3-15 GeV)","V11.2 TkMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(DYLLV11p2),$(DYLLV11p2),$(DYLLV11p2) \
		--numerator "TkMuonIso_EtaPT2to5_000000","TkMuonIso_EtaPT3to15_000000","TkMuonIso_EtaPT15_000000","TkMuonQualIso_EtaPT2to5_000000","TkMuonQualIso_EtaPT3to15_000000","TkMuonQualIso_EtaPT15_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p2_TkMuonExtra_001.pdf
	./Execute \
		--label "V11 TkMuon","V11.2 TkMuon" \
		--file $(DYLLV11),$(DYLLV11p2) \
		--numerator "TkMuonIso_PT_000000","TkMuonQualIso_PT_000000" \
		--denominator "auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p2_TkMuonExtra_002.pdf
	./Execute \
		--label "V11 TkMuon (|eta| < 0.9)","V11 TkMuon (0.9 < |eta| < 1.2)","V11 TkMuon (|eta| > 1.2)","V11.2 TkMuon (|eta| < 0.9)","V11.2 TkMuon (0.9 < |eta| < 1.2)","V11.2 TkMuon (|eta| > 1.2)" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(DYLLV11p2),$(DYLLV11p2),$(DYLLV11p2) \
		--numerator "TkMuonIsoBEta_PT_000000","TkMuonIsoOEta_PT_000000","TkMuonIsoEEta_PT_000000","TkMuonQualIsoBEta_PT_000000","TkMuonQualIsoOEta_PT_000000","TkMuonQualIsoEEta_PT_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p2_TkMuonExtra_003.pdf
	cp V11p2_TkMuonExtra_*pdf ~/public/html
	cp V11p2_TkMuonExtra_*png ~/public/html

V11p1TkMuonPlots: Execute
	./Execute \
		--label "TkMuon (p_{T} = 2-5 GeV)","TkMuon (p_{T} = 3-15 GeV)","TkMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonIso_EtaPT2to5_000000","TkMuonIso_EtaPT3to15_000000","TkMuonIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuon_001.pdf
	./Execute \
		--label "TkMuon (p_{T} = 2-5 GeV)","TkMuon (p_{T} = 3-15 GeV)","TkMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonQualIso_EtaPT2to5_000000","TkMuonQualIso_EtaPT3to15_000000","TkMuonQualIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuon_001Qual.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonIsoBEta_PT_000000","TkMuonIsoOEta_PT_000000","TkMuonIsoEEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p1_TkMuon_002.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonQualIsoBEta_PT_000000","TkMuonQualIsoOEta_PT_000000","TkMuonQualIsoEEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p1_TkMuon_002Qual.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonIsoB_PT_000500","TkMuonIsoO_PT_000500","TkMuonIsoE_PT_000500" \
		--denominator "TkMuonIsoB_PT_000000","TkMuonIsoO_PT_000000","TkMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuon_003.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonQualIsoB_PT_000500","TkMuonQualIsoO_PT_000500","TkMuonQualIsoE_PT_000500" \
		--denominator "TkMuonQualIsoB_PT_000000","TkMuonQualIsoO_PT_000000","TkMuonQualIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuon_003Qual.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonIsoB_PT_002000","TkMuonIsoO_PT_002000","TkMuonIsoE_PT_002000" \
		--denominator "TkMuonIsoB_PT_000000","TkMuonIsoO_PT_000000","TkMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuon_004.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonQualIsoB_PT_002000","TkMuonQualIsoO_PT_002000","TkMuonQualIsoE_PT_002000" \
		--denominator "TkMuonQualIsoB_PT_000000","TkMuonQualIsoO_PT_000000","TkMuonQualIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuon_004Qual.pdf
	./Execute \
		--label "TkMuon (region 1)","TkMuon (region 2)","TkMuon (region 3)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonQualIsoB_EtaPT15_000000","TkMuonQualIsoO_EtaPT15_000000","TkMuonQualIsoE_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 15 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuon_005Qual.pdf
	./Execute \
		--label "TkMuon (region 1)","TkMuon (region 2)","TkMuon (region 3)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "TkMuonQualIsoB_EtaPT3to15_000000","TkMuonQualIsoO_EtaPT3to15_000000","TkMuonQualIsoE_EtaPT3to15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 3-15 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_TkMuon_006Qual.pdf
	cp V11p1_TkMuon_*pdf ~/public/html
	cp V11p1_TkMuon_*png ~/public/html

V11p1STAMuonPlots: Execute
	./Execute \
		--label "STAMuon (p_{T} = 2-5 GeV)","STAMuon (p_{T} = 3-15 GeV)","STAMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "StandaloneMuonIso_EtaPT2to5_000000","StandaloneMuonIso_EtaPT3to15_000000","StandaloneMuonIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_STAMuon_001.pdf
	./Execute \
		--label "STAMuon (p_{T} = 2-5 GeV)","STAMuon (p_{T} = 3-15 GeV)","STAMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "StandaloneMuonQualIso_EtaPT2to5_000000","StandaloneMuonQualIso_EtaPT3to15_000000","StandaloneMuonQualIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_STAMuon_001Qual.pdf
	./Execute \
		--label "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "StandaloneMuonIsoBEta_PT_000000","StandaloneMuonIsoOEta_PT_000000","StandaloneMuonIsoEEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p1_STAMuon_002.pdf
	./Execute \
		--label "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "StandaloneMuonQualIsoBEta_PT_000000","StandaloneMuonQualIsoOEta_PT_000000","StandaloneMuonQualIsoEEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11p1_STAMuon_002Qual.pdf
	./Execute \
		--label "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "StandaloneMuonIsoB_PT_000500","StandaloneMuonIsoO_PT_000500","StandaloneMuonIsoE_PT_000500" \
		--denominator "StandaloneMuonIsoB_PT_000000","StandaloneMuonIsoO_PT_000000","StandaloneMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_STAMuon_003.pdf
	./Execute \
		--label "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "StandaloneMuonQualIsoB_PT_000500","StandaloneMuonQualIsoO_PT_000500","StandaloneMuonQualIsoE_PT_000500" \
		--denominator "StandaloneMuonQualIsoB_PT_000000","StandaloneMuonQualIsoO_PT_000000","StandaloneMuonQualIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_STAMuon_003Qual.pdf
	./Execute \
		--label "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "StandaloneMuonIsoB_PT_002000","StandaloneMuonIsoO_PT_002000","StandaloneMuonIsoE_PT_002000" \
		--denominator "StandaloneMuonIsoB_PT_000000","StandaloneMuonIsoO_PT_000000","StandaloneMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_STAMuon_004.pdf
	./Execute \
		--label "STAMuon (barrel)","STAMuon (overlap)","STAMuon (endcap)" \
		--file $(DYLLV11p1),$(DYLLV11p1),$(DYLLV11p1) \
		--numerator "StandaloneMuonQualIsoB_PT_002000","StandaloneMuonQualIsoO_PT_002000","StandaloneMuonQualIsoE_PT_002000" \
		--denominator "StandaloneMuonQualIsoB_PT_000000","StandaloneMuonQualIsoO_PT_000000","StandaloneMuonQualIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11p1_STAMuon_004Qual.pdf
	cp V11p1_STAMuon_*pdf ~/public/html
	cp V11p1_STAMuon_*png ~/public/html

V11p1PhotonPlots: Execute
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackIDWide_EtaPT25_000000","TkIsoPhotonPVTrackIDWide_EtaPT25_000000","TkIsoPhotonTrackIDWide_EtaPT25_000000","TkIsoPhotonPVTrackIDWide_EtaPT25_000000","TkIsoPhotonTrackIDWide_EtaPT25_000000","TkIsoPhotonPVTrackIDWide_EtaPT25_000000" \
		--denominator "TkPhotonTrackIDIsoWideNoMatch_EtaPT25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT25_000000" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_001.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackIDWide_EtaPT10to25_000000","TkIsoPhotonPVTrackIDWide_EtaPT10to25_000000","TkIsoPhotonTrackIDWide_EtaPT10to25_000000","TkIsoPhotonPVTrackIDWide_EtaPT10to25_000000","TkIsoPhotonTrackIDWide_EtaPT10to25_000000","TkIsoPhotonPVTrackIDWide_EtaPT10to25_000000" \
		--denominator "TkPhotonTrackIDIsoWideNoMatch_EtaPT10to25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT10to25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT10to25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT10to25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT10to25_000000","TkPhotonPVTrackIDIsoWideNoMatch_EtaPT10to25_000000" \
		--title ";Gen. #eta;Matching efficiency (10 < p_{T} < 25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_002.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackIDWide_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackIDWide_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackIDWide_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--denominator "TkPhotonTrackIDIsoWideNoMatch_PTEta15_000000","TkPhotonPVTrackIDIsoNoMatch_PTEta15_000000","TkPhotonTrackIDIsoWideNoMatch_PTEta15_000000","TkPhotonPVTrackIDIsoNoMatch_PTEta15_000000","TkPhotonTrackIDIsoWideNoMatch_PTEta15_000000","TkPhotonPVTrackIDIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_003.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackIDWide_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackIDWide_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackIDWide_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000" \
		--denominator "TkPhotonTrackIDIsoWideNoMatch_PTEtaLarge_000000","TkPhotonPVTrackIDIsoNoMatch_PTEtaLarge_000000","TkPhotonTrackIDIsoWideNoMatch_PTEtaLarge_000000","TkPhotonPVTrackIDIsoNoMatch_PTEtaLarge_000000","TkPhotonTrackIDIsoWideNoMatch_PTEtaLarge_000000","TkPhotonPVTrackIDIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_004.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackID_PTEta15_001500","TkIsoPhotonPVTrackID_PTEta15_001500","TkIsoPhotonTrackID_PTEta15_001500","TkIsoPhotonPVTrackID_PTEta15_001500","TkIsoPhotonTrackID_PTEta15_001500","TkIsoPhotonPVTrackID_PTEta15_001500" \
		--denominator "TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_005.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackID_PTEta15_003000","TkIsoPhotonPVTrackID_PTEta15_003000","TkIsoPhotonTrackID_PTEta15_003000","TkIsoPhotonPVTrackID_PTEta15_003000","TkIsoPhotonTrackID_PTEta15_003000","TkIsoPhotonPVTrackID_PTEta15_003000" \
		--denominator "TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_006.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackID_PTEta15_005000","TkIsoPhotonPVTrackID_PTEta15_005000","TkIsoPhotonTrackID_PTEta15_005000","TkIsoPhotonPVTrackID_PTEta15_005000","TkIsoPhotonTrackID_PTEta15_005000","TkIsoPhotonPVTrackID_PTEta15_005000" \
		--denominator "TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 50 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_007.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackID_PTEtaLarge_001500","TkIsoPhotonPVTrackID_PTEtaLarge_001500","TkIsoPhotonTrackID_PTEtaLarge_001500","TkIsoPhotonPVTrackID_PTEtaLarge_001500","TkIsoPhotonTrackID_PTEtaLarge_001500","TkIsoPhotonPVTrackID_PTEtaLarge_001500" \
		--denominator "TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_008.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackID_PTEtaLarge_003000","TkIsoPhotonPVTrackID_PTEtaLarge_003000","TkIsoPhotonTrackID_PTEtaLarge_003000","TkIsoPhotonPVTrackID_PTEtaLarge_003000","TkIsoPhotonTrackID_PTEtaLarge_003000","TkIsoPhotonPVTrackID_PTEtaLarge_003000" \
		--denominator "TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_009.pdf
	./Execute \
		--label "TkIsoPhoton (HGG)","TkIsoPhotonPV (HGG)","TkIsoPhoton (HHBBGG)","TkIsoPhotonPV (HHBBGG)","TkIsoPhoton (Flat)","TkIsoPhotonPV (Flat)" \
		--file $(HGGV11p1),$(HGGV11p1),$(HHBBGGV11p1),$(HHBBGGV11p1),$(FlatPhotonV11),$(FlatPhotonV11) \
		--numerator "TkIsoPhotonTrackID_PTEtaLarge_005000","TkIsoPhotonPVTrackID_PTEtaLarge_005000","TkIsoPhotonTrackID_PTEtaLarge_005000","TkIsoPhotonPVTrackID_PTEtaLarge_005000","TkIsoPhotonTrackID_PTEtaLarge_005000","TkIsoPhotonPVTrackID_PTEtaLarge_005000" \
		--denominator "TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 50 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -5,-6,-1,-2,-3,-4 \
		--Davignon $(Davignon) --output V11p1_Photon_010.pdf
	cp V11p1_Photon_*pdf ~/public/html/

V11LDRPlots: Execute
	./Execute \
		--label "EG Electron","EG Electron (PT > 10)","EG Photon","EG Photon (PT > 10)","EG Photon","EG Photon (PT > 10)" \
		--file $(DYLLV11),$(DYLLV11),$(Photon1V11),$(Photon1V11),$(Photon2V11),$(Photon2V11) \
		--numerator "EGTrackIDLDR_DR_000000","EGTrackIDLDR_DRPT10_000000","EGLDR_DR_000000","EGLDR_DRPT10_000000","EGLDR_DR_000000","EGLDR_DRPT10_000000" \
		--denominator "simple","simple","simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.50 --line 0 --output V11LDR_001.pdf
	./Execute \
		--label "TkElectron","TkElectron (PT > 10)","TkPhoton","TkPhoton (PT > 10)","TkPhoton","TkPhoton (PT > 10)" \
		--file $(DYLLV11),$(DYLLV11),$(Photon1V11),$(Photon1V11),$(Photon1V11),$(Photon1V11) \
		--numerator "TkElectronLDR_DR_000000","TkElectronLDR_DRPT10_000000","TkPhotonTrackIDLDR_DR_000000","TkPhotonTrackIDLDR_DRPT10_000000","TkPhotonTrackIDLDR_DR_000000","TkPhotonTrackIDLDR_DRPT10_000000" \
		--denominator "simple","simple","simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.50 --line 0 --output V11LDR_002.pdf
	./Execute \
		--label "TkMuon","TkMuon (PT > 10)" \
		--file $(DYLLV11),$(DYLLV11) \
		--numerator "TkMuonLDR_DR_000000","TkMuonLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11LDR_003.pdf
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)","NNTau (PFLoose)","NNTau (PFTight)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauLooseLDR_DR_000000","NNTauLDR_DR_000000","NNTauLoosePFLDR_DR_000000","NNTauPFLDR_DR_000000","CaloTauLDR_DR_000000" \
		--denominator "simple","simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.005 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11LDR_004.pdf
	./Execute \
		--label "NNTau (Loose)","NNTau (Tight)","NNTau (PFLoose)","NNTau (PFTight)","CaloTau" \
		--file $(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11),$(VBFHTauTauV11) \
		--numerator "NNTauLooseLDR_DRPT10_000000","NNTauLDR_DRPT10_000000","NNTauLoosePFLDR_DRPT10_000000","NNTauPFLDR_DRPT10_000000","CaloTauLDR_DRPT10_000000" \
		--denominator "simple","simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.005 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11LDR_005.pdf
	./Execute \
		--label "PuppiJhase1Jet","PuppiPhase1Jet (PT > 10)" \
		--file $(TTbarV11),$(TTbarV11) \
		--numerator "PFPhase1JetLDR_DR_000000","PFPhase1JetLDR_DRPT10_000000" \
		--denominator "simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.01 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V11LDR_006.pdf
	cp V11LDR*pdf ~/public/html/

V11IsoPlots: Execute
	./Execute \
		--label "TkElectron (Barrel)","TkElectron (Endcap)" \
		--file $(DYLLV11),$(DYLLV11) \
		--numerator "TkElectronIso_TkIsoPT10Eta15_000000","TkElectronIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.85 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.20 --line 0.982 --output V11Iso_001.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(Photon1V11),$(Photon1V11) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11Iso_002.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(Photon2V11),$(Photon2V11) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11Iso_003.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(Photon2V11),$(Photon2V11) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0.05 --xmax 0.1 --ymin 0.94 --ymax 0.96 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11Iso_003a.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(Photon2V11),$(Photon2V11) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0.25 --xmax 0.4 --ymin 0.94 --ymax 0.96 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V11Iso_003b.pdf
	cp V11Iso*pdf ~/public/html/

V11EGPlots: Execute
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDWideIso_EtaPT25_000000","TkElectronTrackIDWideIso_EtaPT25_000000","TkIsoElectronWide_EtaPT25_000000","TkIsoPhotonTrackIDWide_EtaPT25_000000" \
		--denominator "auto","auto","TkElectronIsoWideNoMatch_EtaPT25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT25_000000" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_001.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDWideIso_EtaPT10to25_000000","TkElectronTrackIDWideIso_EtaPT10to25_000000","TkIsoElectronWide_EtaPT10to25_000000","TkIsoPhotonTrackIDWide_EtaPT10to25_000000" \
		--denominator "auto","auto","TkElectronIsoWideNoMatch_EtaPT10to25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT10to25_000000" \
		--title ";Gen. #eta;Matching efficiency (10 < p_{T} < 25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_002.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--denominator "auto","auto","TkElectronIsoNoMatch_PTEta15_000000","TkPhotonTrackIDIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_003.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--denominator "auto","auto","TkElectronIsoNoMatch_PTEtaLarge_000000","TkPhotonTrackIDIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_004.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDIso_PTEta15_001500","TkElectronTrackIDIso_PTEta15_001500","TkIsoElectron_PTEta15_001500","TkIsoPhotonTrackID_PTEta15_001500" \
		--denominator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_005.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDIso_PTEta15_003000","TkElectronTrackIDIso_PTEta15_003000","TkIsoElectron_PTEta15_003000","TkIsoPhotonTrackID_PTEta15_003000" \
		--denominator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_006.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDIso_PTEta15_005000","TkElectronTrackIDIso_PTEta15_005000","TkIsoElectron_PTEta15_005000","TkIsoPhotonTrackID_PTEta15_005000" \
		--denominator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, p_{T} > 50 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_007.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDIso_PTEtaLarge_001500","TkElectronTrackIDIso_PTEtaLarge_001500","TkIsoElectron_PTEtaLarge_001500","TkIsoPhotonTrackID_PTEtaLarge_001500" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_008.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDIso_PTEtaLarge_003000","TkElectronTrackIDIso_PTEtaLarge_003000","TkIsoElectron_PTEtaLarge_003000","TkIsoPhotonTrackID_PTEtaLarge_003000" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_009.pdf
	./Execute \
		--label "EG Electron","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11),$(Photon1V11) \
		--numerator "EGTrackIDIso_PTEtaLarge_005000","TkElectronTrackIDIso_PTEtaLarge_005000","TkIsoElectron_PTEtaLarge_005000","TkIsoPhotonTrackID_PTEtaLarge_005000" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, p_{T} > 50 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--color -1,-3,-4,-5 \
		--Davignon $(Davignon) --output V11_EG_010.pdf
	cp V11_EG_*pdf ~/public/html/

V11MuonPlots: Execute
	./Execute \
		--label "TkMuon (p_{T} = 2-5 GeV)","TkMuon (p_{T} = 3-15 GeV)","TkMuon (p_{T} > 15 GeV)" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11) \
		--numerator "TkMuonIso_EtaPT2to5_000000","TkMuonIso_EtaPT3to15_000000","TkMuonIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Muon_001.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11) \
		--numerator "TkMuonIsoBEta_PT_000000","TkMuonIsoOEta_PT_000000","TkMuonIsoEEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11_Muon_002.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11) \
		--numerator "TkMuonIsoB_PT_000500","TkMuonIsoO_PT_000500","TkMuonIsoE_PT_000500" \
		--denominator "TkMuonIsoB_PT_000000","TkMuonIsoO_PT_000000","TkMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Muon_003.pdf
	./Execute \
		--label "TkMuon (barrel)","TkMuon (overlap)","TkMuon (endcap)" \
		--file $(DYLLV11),$(DYLLV11),$(DYLLV11) \
		--numerator "TkMuonIsoB_PT_002000","TkMuonIsoO_PT_002000","TkMuonIsoE_PT_002000" \
		--denominator "TkMuonIsoB_PT_000000","TkMuonIsoO_PT_000000","TkMuonIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_Muon_004.pdf
	cp V11_Muon_*pdf ~/public/html

V11TauNoCaloPlots2: Execute
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_EtaPT40_000000" \
		--denominator "auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_001.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauDRLooseIso_EtaPT40_000000" \
		--denominator "auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_001DR.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_EtaPT20to40_000000" \
		--denominator "auto" \
		--title ";Gen. #eta;Matching efficiency (20 < p_{T} < 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_002.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauDRLooseIso_EtaPT20to40_000000" \
		--denominator "auto" \
		--title ";Gen. #eta;Matching efficiency (20 < p_{T} < 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_002DR.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEta15_000000" \
		--denominator "auto" \
		--title ";Gen. #eta;Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_003.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauDRLooseIso_PTEta15_000000" \
		--denominator "auto" \
		--title ";Gen. #eta;Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_003DR.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEtaLarge_000000" \
		--denominator "auto" \
		--title ";Gen. #eta;Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_004.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauDRLooseIso_PTEtaLarge_000000" \
		--denominator "auto" \
		--title ";Gen. #eta;Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_004DR.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEta15_003000" \
		--denominator "NNTauLooseIso_PTEta15_000000" \
		--title ";Gen. #eta;Trigger efficiency (barrel, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_005.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEta15_007000" \
		--denominator "NNTauLooseIso_PTEta15_000000" \
		--title ";Gen. #eta;Trigger efficiency (barrel, p_{T} > 70 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_006.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEtaLarge_003000" \
		--denominator "NNTauLooseIso_PTEtaLarge_000000" \
		--title ";Gen. #eta;Trigger efficiency (endcap, p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_007.pdf
	./Execute \
		--label "NNTau (Loose)" \
		--file $(HHbbTauTauV11) \
		--numerator "NNTauLooseIso_PTEtaLarge_007000" \
		--denominator "NNTauLooseIso_PTEtaLarge_000000" \
		--title ";Gen. #eta;Trigger efficiency (endcap, p_{T} > 70 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V11_HHTau_008.pdf
	cp V11_HHTau_*pdf ~/public/html/

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

V11JetPlots: Execute
	./Execute \
		--label "PuppiPhase1Jet (p_{T} = 40-100 GeV)","PuppiPhase1Jet (p_{T} > 100 GeV)" \
		--file $(TTbarV11),$(TTbarV11) \
		--numerator "PFPhase1JetWide_EtaPT40to100_000000","PFPhase1JetWide_EtaPT100_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency" --xmin -5 --xmax 5 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11_Jet_001.pdf
	./Execute \
		--label "PuppiPhase1Jet (barrel)","PuppiPhase1Jet (endcap)","PuppiPhase1Jet (forward)" \
		--file $(TTbarV11),$(TTbarV11),$(TTbarV11) \
		--numerator "PFPhase1Jet_PTEta15_000000","PFPhase1Jet_PTEtaLarge_000000","PFPhase1JetForward_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11_Jet_002.pdf
	./Execute \
		--label "PuppiPhase1Jet (barrel)","PuppiPhase1Jet (endcap)","PuppiPhase1Jet (forward)" \
		--file $(TTbarV11),$(TTbarV11),$(TTbarV11) \
		--numerator "PFPhase1Jet_PTEta15_005000","PFPhase1Jet_PTEtaLarge_005000","PFPhase1JetForward_PT_005000" \
		--denominator "PFPhase1Jet_PTEta15_000000","PFPhase1Jet_PTEtaLarge_000000","PFPhase1JetForward_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (p_{T} > 50 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11_Jet_003.pdf
	./Execute \
		--label "PuppiPhase1Jet (barrel)","PuppiPhase1Jet (endcap)","PuppiPhase1Jet (forward)" \
		--file $(TTbarV11),$(TTbarV11),$(TTbarV11) \
		--numerator "PFPhase1Jet_PTEta15_012000","PFPhase1Jet_PTEtaLarge_012000","PFPhase1JetForward_PT_012000" \
		--denominator "PFPhase1Jet_PTEta15_000000","PFPhase1Jet_PTEtaLarge_000000","PFPhase1JetForward_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (p_{T} > 120 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11_Jet_004.pdf
	cp V11_Jet_*pdf ~/public/html

V11HTMETPlots: Execute
	./Execute \
		--label "PuppiHT (200 GeV)","PuppiHT (350 GeV)" \
		--file $(TTbarV11),$(TTbarV11) \
		--numerator "PFPhase1HT_PT_020000","PFPhase1HT_PT_035000" \
		--denominator "PFPhase1HT_PT_000000","PFPhase1HT_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11_HTMET_001.pdf
	./Execute \
		--label "PuppiMET (70 GeV)","PuppiMET (150 GeV)" \
		--file $(TTbarV11),$(TTbarV11) \
		--numerator "PuppiMET_PT_007000","PuppiMET_PT_015000" \
		--denominator "PuppiMET_PT_000000","PuppiMET_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V11_HTMET_002.pdf
	cp V11_HTMET*pdf ~/public/html/

Execute: PlotComparison.cpp
	CompileRootMacro PlotComparison.cpp Execute
