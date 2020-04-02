DYLL    = DYLL_V8p2.root
HGG     = HGG_V7p4.root
NewDYLL = DYLL_V9.root
NewHGG  = HGG_V8p2.root
HTauTau = HTauTau_V8p2.root
SingleTau = SingleTau_V9.root
WLNu    = WLNu_V6.root
VBFHInv = VBFHInv_V7p42.root
TTbar   = TTbar_V7p42.root
QCD     = QCD_V7p42.root
NewQCD  = QCD_V9.root

DYLLV10       = DYLL_V10p7.root
DYLLLDRV10    = DYLL_V10p7.root
HGGV10        = HGG_V10p2.root
HGGLDRV10     = HGG_V10p2.root
HTauTauV10    = HTauTau_V10p5.root
HTauTauLDRV10 = HTauTau_V10p5.root
HHbbTauTauV10    = HHbbTauTau_Tau_V10p5.root
HHbbTauTauLDRV10 = HHbbTauTau_Tau_V10p5.root
QCDV10        = QCD_V10p3.root
QCDLDRV10     = QCD_LDR_V10p3.root
TTbarV10      = TTbar_V10p3.root
TTbarLDRV10   = TTbar_LDR_V10p3.root
HadronicTTbarV10      = HadronicTTbar_V10p3.root
VBFHInvV10    = VBFHInv_V10p3.root
DarkPhotonV10 = DarkPhoton_MuEG_V10p5.root
Davignon  = true
DarkSUSYCT1V10 = DarkSUSYCT1_V10p5.root
DarkSUSYCT10V10 = DarkSUSYCT10_V10p5.root
DarkSUSYCT100V10 = DarkSUSYCT100_V10p5.root
DarkSUSYCT1000V10 = DarkSUSYCT1000_V10p5.root
DarkSUSYCT10000V10 = DarkSUSYCT10000_V10p7.root
DisplacedMuonV10 = DisplacedMuon_V10p7.root

# default: V10Plots V10PlotsPart2 V10PlotsPart3 V10PlotsPart4 V10PlotsPart5 V10PlotsPart6 V10PlotsPart7
default: V10PlotsPart7

V10Plots: Execute
	./Execute \
		--label "EG Electron","EG Photon","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDWideIso_EtaPT25_000000","EGWideIso_EtaPT25_000000","TkElectronV2TrackIDWideIso_EtaPT25_000000","TkIsoElectronV2Wide_EtaPT25_000000","TkIsoPhotonTrackIDWide_EtaPT25_000000" \
		--denominator "auto","auto","auto","TkElectronV2IsoWideNoMatch_EtaPT25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT25_000000" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_001.pdf
	./Execute \
		--label "EG Electron","EG Photon","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDWideIso_EtaPT10to25_000000","EGWideIso_EtaPT10to25_000000","TkElectronV2TrackIDWideIso_EtaPT10to25_000000","TkIsoElectronV2Wide_EtaPT10to25_000000","TkIsoPhotonTrackIDWide_EtaPT10to25_000000" \
		--denominator "auto","auto","auto","TkElectronV2IsoWideNoMatch_EtaPT10to25_000000","TkPhotonTrackIDIsoWideNoMatch_EtaPT10to25_000000" \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 10-25 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_002.pdf
	./Execute \
		--label "EG Electron","EG Photon","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDIso_PTEta15_000000","EGIso_PTEta15_000000","TkElectronV2TrackIDIso_PTEta15_000000","TkIsoElectronV2_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--denominator "auto","auto","auto","TkElectronV2IsoNoMatch_PTEta15_000000","TkPhotonTrackIDIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_003.pdf
	./Execute \
		--label "EG Electron","EG Photon","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDIso_PTEtaLarge_000000","EGIso_PTEtaLarge_000000","TkElectronV2TrackIDIso_PTEtaLarge_000000","TkIsoElectronV2_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--denominator "auto","auto","auto","TkElectronV2IsoNoMatch_PTEtaLarge_000000","TkPhotonTrackIDIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_004.pdf
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIso_EtaPT15_000000","TkMuonIso_EtaPT15_000000","TkMuonStubWideIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 15 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_005.pdf
	./Execute \
		--label "TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10) \
		--numerator "TkMuonIso_EtaPT2to5_000000","TkMuonStubWideIso_EtaPT2to5_000000" \
		--denominator "auto","auto" \
		--color -2,-3 \
		--legendx 0.375 --legendy 0.65 \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 2-5 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_006.pdf
	./Execute \
		--label "TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10) \
		--numerator "TkMuonIso_EtaPT2to5_000000","TkMuonStubWideIsoEBO_EtaPT2to5_000000" \
		--denominator "auto","auto" \
		--color -2,-3 \
		--legendx 0.375 --legendy 0.65 \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 2-5 GeV)" --xmin -3.0 --xmax 3.0 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_006b.pdf
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIsoBEta_PT_000000","TkMuonIsoBEta_PT_000000","TkMuonStubIsoBEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_007.pdf
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIsoOEta_PT_000000","TkMuonIsoOEta_PT_000000","TkMuonStubIsoOEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (overlap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_008.pdf
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIsoEEta_PT_000000","TkMuonIsoEEta_PT_000000","TkMuonStubIsoEEta_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_009.pdf
	./Execute \
		--label "TkMuonStub" \
		--file $(DYLLV10) \
		--numerator "TkMuonStubIsoExtendedEta_PT_000000" \
		--denominator "auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (|#eta| = 2.4-2.8)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_010.pdf
	./Execute \
		--label "EG Electron","EG Photon","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDIso_PTEta15_001500","EGIso_PTEta15_001500","TkElectronV2TrackIDIso_PTEta15_001500","TkIsoElectronV2_PTEta15_001500","TkIsoPhotonTrackID_PTEta15_001500" \
		--denominator "EGTrackIDIso_PTEta15_000000","EGIso_PTEta15_000000","TkElectronV2TrackIDIso_PTEta15_000000","TkIsoElectronV2_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_011.pdf
	./Execute \
		--label "EG","TkElectron","TkIsoElectron","TkIsoPhoton","NONE","NONE","NONE","NONE","NONE","NONE","NONE","NONE" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDIso_PTEta15_001500","TkElectronV2TrackIDIso_PTEta15_001500","TkIsoElectronV2_PTEta15_001500","TkIsoPhotonTrackID_PTEta15_001500","EGTrackIDIso_PTEta15_003000","TkElectronV2TrackIDIso_PTEta15_003000","TkIsoElectronV2_PTEta15_003000","TkIsoPhotonTrackID_PTEta15_003000","EGTrackIDIso_PTEta15_005000","TkElectronV2TrackIDIso_PTEta15_005000","TkIsoElectronV2_PTEta15_005000","TkIsoPhotonTrackID_PTEta15_005000" \
		--denominator "EGTrackIDIso_PTEta15_000000","TkElectronV2TrackIDIso_PTEta15_000000","TkIsoElectronV2_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","EGTrackIDIso_PTEta15_000000","TkElectronV2TrackIDIso_PTEta15_000000","TkIsoElectronV2_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","EGTrackIDIso_PTEta15_000000","TkElectronV2TrackIDIso_PTEta15_000000","TkIsoElectronV2_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 15, 30, 50 GeV)" --xmin 0 --xmax 120 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.55 --legendy 0.20 \
		--color -1,-2,-3,-4,-1,-2,-3,-4,-1,-2,-3,-4,-5 \
		--line 1.00,0.95 \
		--Davignon $(Davignon) --output V10_011NewYear.pdf
	./Execute \
		--label "EG","TkElectron","TkIsoElectron","TkIsoPhoton","NONE","NONE","NONE","NONE","NONE","NONE","NONE","NONE" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDIso_PTEta15_001500","TkElectronV2TrackIDIso_PTEta15_001500","TkIsoElectronV2_PTEta15_001500","TkIsoPhotonTrackID_PTEta15_001500","EGTrackIDIso_PTEta15_003000","TkElectronV2TrackIDIso_PTEta15_003000","TkIsoElectronV2_PTEta15_003000","TkIsoPhotonTrackID_PTEta15_003000","EGTrackIDIso_PTEta15_005000","TkElectronV2TrackIDIso_PTEta15_005000","TkIsoElectronV2_PTEta15_005000","TkIsoPhotonTrackID_PTEta15_005000" \
		--denominator "EGTrackIDIso_PTEta15_000000","TkElectronV2TrackIDIso_PTEta15_000000","TkIsoElectronV2_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","EGTrackIDIso_PTEta15_000000","TkElectronV2TrackIDIso_PTEta15_000000","TkIsoElectronV2_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000","EGTrackIDIso_PTEta15_000000","TkElectronV2TrackIDIso_PTEta15_000000","TkIsoElectronV2_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency" --xmin 0 --xmax 120 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.55 --legendy 0.20 \
		--color -1,-2,-3,-4,-1,-2,-3,-4,-1,-2,-3,-4,-5 \
		--marker 20,21,22,23,24,20,21,22,23,24,20,21,22,23,24 \
		--line 1.00,0.95 \
		--text 0.55,0.55,"Barrel |#eta| < 1.5",0.55,0.50,"L1 p_{T} > 15/30/50 GeV" \
		--Davignon $(Davignon) --output V10_011NewYearV2.pdf
	./Execute \
		--label "EG Electron","EG Photon","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDIso_PTEta15_003000","EGIso_PTEta15_003000","TkElectronV2TrackIDIso_PTEta15_003000","TkIsoElectronV2_PTEta15_003000","TkIsoPhotonTrackID_PTEta15_003000" \
		--denominator "EGTrackIDIso_PTEta15_000000","EGIso_PTEta15_000000","TkElectronV2TrackIDIso_PTEta15_000000","TkIsoElectronV2_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_012.pdf
	./Execute \
		--label "EG Electron","EG Photon","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDIso_PTEtaLarge_001500","EGIso_PTEtaLarge_001500","TkElectronV2TrackIDIso_PTEtaLarge_001500","TkIsoElectronV2_PTEtaLarge_001500","TkIsoPhotonTrackID_PTEtaLarge_001500" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","EGIso_PTEtaLarge_000000","TkElectronV2TrackIDIso_PTEtaLarge_000000","TkIsoElectronV2_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_014.pdf
	./Execute \
		--label "EG Electron","EG Photon","TkElectron","TkIsoElectron","TkIsoPhoton" \
		--file $(DYLLV10),$(HGGV10),$(DYLLV10),$(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDIso_PTEtaLarge_003000","EGIso_PTEtaLarge_003000","TkElectronV2TrackIDIso_PTEtaLarge_003000","TkIsoElectronV2_PTEtaLarge_003000","TkIsoPhotonTrackID_PTEtaLarge_003000" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","EGIso_PTEtaLarge_000000","TkElectronV2TrackIDIso_PTEtaLarge_000000","TkIsoElectronV2_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_015.pdf
	./Execute \
		--label "EG Electron","EG Photon" \
		--file $(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDExtendedIso_PT_001500","EGExtendedIso_PT_001500" \
		--denominator "EGTrackIDExtendedIso_PT_000000","EGExtendedIso_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (|#eta| = 2.4-2.8, L1 p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_016.pdf
	./Execute \
		--label "EG Electron","EG Photon" \
		--file $(DYLLV10),$(HGGV10) \
		--numerator "EGTrackIDExtendedIso_PT_003000","EGExtendedIso_PT_003000" \
		--denominator "EGTrackIDExtendedIso_PT_000000","EGExtendedIso_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (|#eta| = 2.4-2.8, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_017.pdf
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIsoB_PT_000500","TkMuonIsoB_PT_000500","TkMuonStubIsoB_PT_000500" \
		--denominator "StandaloneMuonIsoB_PT_000000","TkMuonIsoB_PT_000000","TkMuonStubIsoB_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_018.pdf
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIsoB_PT_002000","TkMuonIsoB_PT_002000","TkMuonStubIsoB_PT_002000" \
		--denominator "StandaloneMuonIsoB_PT_000000","TkMuonIsoB_PT_000000","TkMuonStubIsoB_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_019.pdf \
		--legendx 0.50 --legendy 0.20
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIsoO_PT_000500","TkMuonIsoO_PT_000500","TkMuonStubIsoO_PT_000500" \
		--denominator "StandaloneMuonIsoO_PT_000000","TkMuonIsoO_PT_000000","TkMuonStubIsoO_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (overlap, L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_020.pdf
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIsoO_PT_002000","TkMuonIsoO_PT_002000","TkMuonStubIsoO_PT_002000" \
		--denominator "StandaloneMuonIsoO_PT_000000","TkMuonIsoO_PT_000000","TkMuonStubIsoO_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (overlap, L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--legendx 0.50 --legendy 0.20 \
		--Davignon $(Davignon) --output V10_021.pdf
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIsoE_PT_000500","TkMuonIsoE_PT_000500","TkMuonStubIsoE_PT_000500" \
		--denominator "StandaloneMuonIsoE_PT_000000","TkMuonIsoE_PT_000000","TkMuonStubIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 5 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_022.pdf
	./Execute \
		--label "STA Muon","TkMuon","TkMuonStub" \
		--file $(DYLLV10),$(DYLLV10),$(DYLLV10) \
		--numerator "StandaloneMuonIsoE_PT_002000","TkMuonIsoE_PT_002000","TkMuonStubIsoE_PT_002000" \
		--denominator "StandaloneMuonIsoE_PT_000000","TkMuonIsoE_PT_000000","TkMuonStubIsoE_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_023.pdf \
		--legendx 0.50 --legendy 0.20
	./Execute \
		--label "TkMuonStub" \
		--file $(DYLLV10) \
		--numerator "TkMuonStubIsoExtended_PT_002000" \
		--denominator "TkMuonStubIsoExtended_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (|#eta| > 2.4, L1 p_{T} > 20 GeV)" --xmin 0 --xmax 50 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_024.pdf \
		--legendx 0.5 --legendy 0.2
	cp V10_*pdf ~/public/html/

V10PlotsPart2Old: Execute
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","HPSPFTau2","HPSPFTau2 (Tight)","NNPuppiTau (Tight)","NNPuppiTau (Loose)" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_EtaPT40_000000","PFIsoTau_EtaPT40_000000","HPSTauIso_EtaPT40_000000","HPSIsoTau_EtaPT40_000000","NNTauIso_EtaPT40_000000","NNTauLooseIso_EtaPT40_000000" \
		--denominator "auto","PFTauIsoNoMatch_EtaPT40_000000","auto","HPSTauIsoNoMatch_EtaPT40_000000","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_025a.pdf
	./Execute \
		--label "tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "TkEGTauIso_EtaPT40_000000","CaloTauIso_EtaPT40_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_025b.pdf
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","HPSPFTau2","HPSPFTau2 (Tight)","NNPuppiTau (Tight)","NNPuppiTau (Loose)" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_EtaPT20to40_000000","PFIsoTau_EtaPT20to40_000000","HPSTauIso_EtaPT20to40_000000","HPSIsoTau_EtaPT20to40_000000","NNTauIso_EtaPT20to40_000000","NNTauLooseIso_EtaPT20to40_000000" \
		--denominator "auto","PFTauIsoNoMatch_EtaPT20to40_000000","auto","HPSTauIsoNoMatch_EtaPT20to40_000000","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 20-40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_026a.pdf
	./Execute \
		--label "tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "TkEGTauIso_EtaPT20to40_000000","CaloTauIso_EtaPT20to40_000000" \
		--denominator "auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 20-40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_026b.pdf
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","HPSPFTau2","HPSPFTau2 (Tight)","NNPuppiTau (Tight)","NNPuppiTau (Loose)" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEta15_000000","PFIsoTau_PTEta15_000000","HPSTauIso_PTEta15_000000","HPSIsoTau_PTEta15_000000","NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000" \
		--denominator "auto","PFTauIsoNoMatch_PTEta15_000000","auto","HPSTauIsoNoMatch_PTEta15_000000","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_027a.pdf
	./Execute \
		--label "tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "TkEGTauIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_027b.pdf
	./Execute \
		--label "HPSPFTau_1","HPSPFTau_2","NNPuppiTau (Tight)","NNPuppiTau (Loose)","NNPuppiTau (NoID)","NNPFTau (NoID)" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEta15_000000","HPSTauIso_PTEta15_000000","NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","NNTauNoIDIso_PTEta15_000000","NNPFTauNoIDIso_PTEta15_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_027c.pdf --legendx 0.50 --legendy 0.12
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","HPSPFTau2","HPSPFTau2 (Tight)","NNPuppiTau (Tight)","NNPuppiTau (Loose)" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEtaLarge_000000","PFIsoTau_PTEtaLarge_000000","HPSTauIso_PTEtaLarge_000000","HPSIsoTau_PTEtaLarge_000000","NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000" \
		--denominator "auto","PFTauIsoNoMatch_PTEtaLarge_000000","auto","HPSTauIsoNoMatch_PTEtaLarge_000000","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_028a.pdf
	./Execute \
		--label "tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "TkEGTauIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_028b.pdf
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","HPSPFTau2","HPSPFTau2 (Tight)","NNPuppiTau (Tight)","NNPuppiTau (Loose)" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEta15_003000","PFIsoTau_PTEta15_003000","HPSTauIso_PTEta15_003000","HPSIsoTau_PTEta15_003000","NNTauIso_PTEta15_003000","NNTauLooseIso_PTEta15_003000" \
		--denominator "PFTauIso_PTEta15_000000","PFIsoTau_PTEta15_000000","HPSTauIso_PTEta15_000000","HPSIsoTau_PTEta15_000000","NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_029a.pdf
	./Execute \
		--label "tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "TkEGTauIso_PTEta15_003000","CaloTauIso_PTEta15_003000" \
		--denominator "TkEGTauIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_029b.pdf
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","HPSPFTau2","HPSPFTau2 (Tight)","NNPuppiTau (Tight)","NNPuppiTau (Loose)" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEtaLarge_003000","PFIsoTau_PTEtaLarge_003000","HPSTauIso_PTEtaLarge_003000","HPSIsoTau_PTEtaLarge_003000","NNTauIso_PTEtaLarge_003000","NNTauLooseIso_PTEtaLarge_003000" \
		--denominator "PFTauIso_PTEtaLarge_000000","PFIsoTau_PTEtaLarge_000000","HPSTauIso_PTEtaLarge_000000","HPSIsoTau_PTEtaLarge_000000","NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_030a.pdf
	./Execute \
		--label "tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "TkEGTauIso_PTEtaLarge_003000","CaloTauIso_PTEtaLarge_003000" \
		--denominator "TkEGTauIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_030b.pdf
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","HPSPFTau2","HPSPFTau2 (Tight)","NNPuppiTau (Tight)","NNPuppiTau (Loose)" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEta15_007000","PFIsoTau_PTEta15_007000","HPSTauIso_PTEta15_007000","HPSIsoTau_PTEta15_007000","NNTauIso_PTEta15_007000","NNTauLooseIso_PTEta15_007000" \
		--denominator "PFTauIso_PTEta15_000000","PFIsoTau_PTEta15_000000","HPSTauIso_PTEta15_000000","HPSIsoTau_PTEta15_000000","NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_031a.pdf
	./Execute \
		--label "tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "TkEGTauIso_PTEta15_007000","CaloTauIso_PTEta15_007000" \
		--denominator "TkEGTauIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_031b.pdf
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","HPSPFTau2","HPSPFTau2 (Tight)","NNPuppiTau (Tight)","NNPuppiTau (Loose)" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEtaLarge_007000","PFIsoTau_PTEtaLarge_007000","HPSTauIso_PTEtaLarge_007000","HPSIsoTau_PTEtaLarge_007000","NNTauIso_PTEtaLarge_007000","NNTauLooseIso_PTEtaLarge_007000" \
		--denominator "PFTauIso_PTEtaLarge_000000","PFIsoTau_PTEtaLarge_000000","HPSTauIso_PTEtaLarge_000000","HPSIsoTau_PTEtaLarge_000000","NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_032a.pdf
	./Execute \
		--label "tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "TkEGTauIso_PTEtaLarge_007000","CaloTauIso_PTEtaLarge_007000" \
		--denominator "TkEGTauIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_032b.pdf
	cp V10*pdf ~/public/html/

V10PlotsPart2: Execute
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_EtaPT40_000000","PFIsoTau_EtaPT40_000000","NNTauIso_EtaPT40_000000","NNTauLooseIso_EtaPT40_000000","TkEGTauIso_EtaPT40_000000","CaloTauIso_EtaPT40_000000" \
		--denominator "auto","PFTauIsoNoMatch_EtaPT40_000000","auto","auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_025a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_EtaPT40_000000","NNTauLooseIso_EtaPT40_000000","CaloTauIso_EtaPT40_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_025b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_EtaPT20to40_000000","PFIsoTau_EtaPT20to40_000000","NNTauIso_EtaPT20to40_000000","NNTauLooseIso_EtaPT20to40_000000","TkEGTauIso_EtaPT20to40_000000","CaloTauIso_EtaPT20to40_000000" \
		--denominator "auto","PFTauIsoNoMatch_EtaPT20to40_000000","auto","auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 20-40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_026a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_EtaPT20to40_000000","NNTauLooseIso_EtaPT20to40_000000","CaloTauIso_EtaPT20to40_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 20-40 GeV)" --xmin -2.5 --xmax 2.5 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_026b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEta15_000000","PFIsoTau_PTEta15_000000","NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","TkEGTauIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--denominator "auto","PFTauIsoNoMatch_PTEta15_000000","auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_027a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_027b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEtaLarge_000000","PFIsoTau_PTEtaLarge_000000","NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000","TkEGTauIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--denominator "auto","PFTauIsoNoMatch_PTEtaLarge_000000","auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_028a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--denominator "auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_028b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEta15_003000","PFIsoTau_PTEta15_003000","NNTauIso_PTEta15_003000","NNTauLooseIso_PTEta15_003000","TkEGTauIso_PTEta15_003000","CaloTauIso_PTEta15_003000" \
		--denominator "PFTauIso_PTEta15_000000","PFIsoTau_PTEta15_000000","NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","TkEGTauIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_029a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEta15_003000","NNTauLooseIso_PTEta15_003000","CaloTauIso_PTEta15_003000" \
		--denominator "NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_029b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEtaLarge_003000","PFIsoTau_PTEtaLarge_003000","NNTauIso_PTEtaLarge_003000","NNTauLooseIso_PTEtaLarge_003000","TkEGTauIso_PTEtaLarge_003000","CaloTauIso_PTEtaLarge_003000" \
		--denominator "PFTauIso_PTEtaLarge_000000","PFIsoTau_PTEtaLarge_000000","NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000","TkEGTauIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_030a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEtaLarge_003000","NNTauLooseIso_PTEtaLarge_003000","CaloTauIso_PTEtaLarge_003000" \
		--denominator "NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_030b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEta15_007000","PFIsoTau_PTEta15_007000","NNTauIso_PTEta15_007000","NNTauLooseIso_PTEta15_007000","TkEGTauIso_PTEta15_007000","CaloTauIso_PTEta15_007000" \
		--denominator "PFTauIso_PTEta15_000000","PFIsoTau_PTEta15_000000","NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","TkEGTauIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_031a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEta15_007000","NNTauLooseIso_PTEta15_007000","CaloTauIso_PTEta15_007000" \
		--denominator "NNTauIso_PTEta15_000000","NNTauLooseIso_PTEta15_000000","CaloTauIso_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_031b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEtaLarge_007000","PFIsoTau_PTEtaLarge_007000","NNTauIso_PTEtaLarge_007000","NNTauLooseIso_PTEtaLarge_007000","TkEGTauIso_PTEtaLarge_007000","CaloTauIso_PTEtaLarge_007000" \
		--denominator "PFTauIso_PTEtaLarge_000000","PFIsoTau_PTEtaLarge_000000","NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000","TkEGTauIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_032a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEtaLarge_007000","NNTauLooseIso_PTEtaLarge_007000","CaloTauIso_PTEtaLarge_007000" \
		--denominator "NNTauIso_PTEtaLarge_000000","NNTauLooseIso_PTEtaLarge_000000","CaloTauIso_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_032b.pdf --color -3,-4,-6
	cp V10*pdf ~/public/html/

V10PlotsPart2Combined: Execute
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEta15_003000","PFIsoTau_PTEta15_003000","NNTauIso_PTEta15_003000","NNTauLooseIso_PTEta15_003000","TkEGTauIso_PTEta15_003000","CaloTauIso_PTEta15_003000" \
		--denominator "PFTauIsoNoMatch_PTEta15_000000","PFIsoTauNoMatch_PTEta15_000000","NNTauIsoNoMatch_PTEta15_000000","NNTauLooseIsoNoMatch_PTEta15_000000","TkEGTauIsoNoMatch_PTEta15_000000","CaloTauIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (barrel, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10Combined_029a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEta15_003000","NNTauLooseIso_PTEta15_003000","CaloTauIso_PTEta15_003000" \
		--denominator "NNTauIsoNoMatch_PTEta15_000000","NNTauLooseIsoNoMatch_PTEta15_000000","CaloTauIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (barrel, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10Combined_029b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEtaLarge_003000","PFIsoTau_PTEtaLarge_003000","NNTauIso_PTEtaLarge_003000","NNTauLooseIso_PTEtaLarge_003000","TkEGTauIso_PTEtaLarge_003000","CaloTauIso_PTEtaLarge_003000" \
		--denominator "PFTauIsoNoMatch_PTEtaLarge_000000","PFIsoTauNoMatch_PTEtaLarge_000000","NNTauIsoNoMatch_PTEtaLarge_000000","NNTauLooseIsoNoMatch_PTEtaLarge_000000","TkEGTauIsoNoMatch_PTEtaLarge_000000","CaloTauIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (endcap, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10Combined_030a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEtaLarge_003000","NNTauLooseIso_PTEtaLarge_003000","CaloTauIso_PTEtaLarge_003000" \
		--denominator "NNTauIsoNoMatch_PTEtaLarge_000000","NNTauLooseIsoNoMatch_PTEtaLarge_000000","CaloTauIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (endcap, L1 p_{T} > 30 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10Combined_030b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEta15_007000","PFIsoTau_PTEta15_007000","NNTauIso_PTEta15_007000","NNTauLooseIso_PTEta15_007000","TkEGTauIso_PTEta15_007000","CaloTauIso_PTEta15_007000" \
		--denominator "PFTauIsoNoMatch_PTEta15_000000","PFIsoTauNoMatch_PTEta15_000000","NNTauIsoNoMatch_PTEta15_000000","NNTauLooseIsoNoMatch_PTEta15_000000","TkEGTauIsoNoMatch_PTEta15_000000","CaloTauIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (barrel, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 --legendx 0.48 --legendy 0.12 \
		--Davignon $(Davignon) --output V10Combined_031a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEta15_007000","NNTauLooseIso_PTEta15_007000","CaloTauIso_PTEta15_007000" \
		--denominator "NNTauIsoNoMatch_PTEta15_000000","NNTauLooseIsoNoMatch_PTEta15_000000","CaloTauIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (barrel, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 --legendx 0.48 --legendy 0.12 \
		--Davignon $(Davignon) --output V10Combined_031b.pdf --color -3,-4,-6
	./Execute \
		--label "HPSPFTau1","HPSPFTau1 (Medium)","NNPuppiTau (Tight)","NNPuppiTau (Loose)","tkEGTau","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "PFTauIso_PTEtaLarge_007000","PFIsoTau_PTEtaLarge_007000","NNTauIso_PTEtaLarge_007000","NNTauLooseIso_PTEtaLarge_007000","TkEGTauIso_PTEtaLarge_007000","CaloTauIso_PTEtaLarge_007000" \
		--denominator "PFTauIsoNoMatch_PTEtaLarge_000000","PFIsoTauNoMatch_PTEtaLarge_000000","NNTauIsoNoMatch_PTEtaLarge_000000","NNTauLooseIsoNoMatch_PTEtaLarge_000000","TkEGTauIsoNoMatch_PTEtaLarge_000000","CaloTauIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (endcap, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 --legendx 0.48 --legendy 0.12 \
		--Davignon $(Davignon) --output V10Combined_032a.pdf
	./Execute \
		--label "NNPuppiTau (Tight)","NNPuppiTau (Loose)","CaloTau" \
		--file $(HHbbTauTauV10),$(HHbbTauTauV10),$(HHbbTauTauV10) \
		--numerator "NNTauIso_PTEtaLarge_007000","NNTauLooseIso_PTEtaLarge_007000","CaloTauIso_PTEtaLarge_007000" \
		--denominator "NNTauIsoNoMatch_PTEtaLarge_000000","NNTauLooseIsoNoMatch_PTEtaLarge_000000","CaloTauIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (endcap, L1 p_{T} > 70 GeV)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 --legendx 0.48 --legendy 0.12 \
		--Davignon $(Davignon) --output V10Combined_032b.pdf --color -3,-4,-6
	cp V10*pdf ~/public/html/


V10PlotsPart3: Execute
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJetWide_EtaPT100_000000","PFPhase1JetWide_EtaPT100_000000","TrackerJet_EtaPT100_000000","CaloJetWide_EtaPT100_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 100 GeV)" --xmin -5 --xmax 5 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_033.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJetWide_EtaPT40to100_000000","PFPhase1JetWide_EtaPT40to100_000000","TrackerJet_EtaPT40to100_000000","CaloJetWide_EtaPT40to100_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 40-100 GeV)" --xmin -5 --xmax 5 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_034.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJet_PTEta15_000000","PFPhase1Jet_PTEta15_000000","TrackerJet_PTEta15_000000","CaloJet_PTEta15_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_035.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJet_PTEtaLarge_000000","PFPhase1Jet_PTEtaLarge_000000","TrackerJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_036.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJetForward_PT_000000","PFPhase1JetForward_PT_000000","TrackerJetForward_PT_000000","CaloJetFoward_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (|eta| > 2.4)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_037.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJet_PTEta15_005000","PFPhase1Jet_PTEta15_005000","TrackerJet_PTEta15_005000","CaloJet_PTEta15_005000" \
		--denominator "PuppiJet_PTEta15_000000","PFPhase1Jet_PTEta15_000000","TrackerJet_PTEta15_000000","CaloJet_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 50 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_038.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJet_PTEtaLarge_005000","PFPhase1Jet_PTEtaLarge_005000","TrackerJet_PTEtaLarge_005000","CaloJet_PTEtaLarge_005000" \
		--denominator "PuppiJet_PTEtaLarge_000000","PFPhase1Jet_PTEtaLarge_000000","TrackerJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 50 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_039.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJetForward_PT_005000","PFPhase1JetForward_PT_005000","TrackerJetForward_PT_005000","CaloJetFoward_PT_005000" \
		--denominator "PuppiJetForward_PT_000000","PFPhase1JetForward_PT_000000","TrackerJetForward_PT_000000","CaloJetFoward_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (|#eta| > 2.4, L1 p_{T} > 50 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_040.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJet_PTEta15_012000","PFPhase1Jet_PTEta15_012000","TrackerJet_PTEta15_012000","CaloJet_PTEta15_012000" \
		--denominator "PuppiJet_PTEta15_000000","PFPhase1Jet_PTEta15_000000","TrackerJet_PTEta15_000000","CaloJet_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 120 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_041.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJet_PTEtaLarge_012000","PFPhase1Jet_PTEtaLarge_012000","TrackerJet_PTEtaLarge_012000","CaloJet_PTEtaLarge_012000" \
		--denominator "PuppiJet_PTEtaLarge_000000","PFPhase1Jet_PTEtaLarge_000000","TrackerJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 120 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_042.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiJetForward_PT_012000","PFPhase1JetForward_PT_012000","TrackerJetForward_PT_012000","CaloJetFoward_PT_012000" \
		--denominator "PuppiJetForward_PT_000000","PFPhase1JetForward_PT_000000","TrackerJetForward_PT_000000","CaloJetFoward_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (|#eta| > 2.4, L1 p_{T} > 120 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_043.pdf
	./Execute \
		--label "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiHT_PT_035000","PFPhase1HT_PT_035000","TrackerHT_PT_035000","CaloHT_PT_035000" \
		--denominator "PuppiHT_PT_000000","PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 350 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_044.pdf
	./Execute \
		--label "PuppiHT","TrackerHT","CaloHT" \
		--file $(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PFPhase1HT_PT_035000","TrackerHT_PT_035000","CaloHT_PT_035000" \
		--denominator "PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 350 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_044YesPhase1HT.pdf
	./Execute \
		--label "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiHT_PT_020000","PFPhase1HT_PT_020000","TrackerHT_PT_020000","CaloHT_PT_020000" \
		--denominator "PuppiHT_PT_000000","PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 200 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_044Low.pdf
	./Execute \
		--label "PuppiHT","TrackerHT","CaloHT" \
		--file $(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PFPhase1HT_PT_020000","TrackerHT_PT_020000","CaloHT_PT_020000" \
		--denominator "PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 200 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_044LowYesPhase1HT.pdf
	./Execute \
		--label "PuppiMET","TrackerMET" \
		--file $(VBFHInvV10),$(VBFHInvV10) \
		--numerator "PuppiMET_PT_015000","TrackerMET_PT_015000" \
		--denominator "PuppiMET_PT_000000","TrackerMET_PT_000000" \
		--title ";Gen. MET (GeV);Trigger efficiency (L1 p_{T} > 150 GeV);" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_045.pdf
	./Execute \
		--label "PuppiMET","TrackerMET" \
		--file $(TTbarV10),$(TTbarV10) \
		--numerator "PuppiMET_PT_015000","TrackerMET_PT_015000" \
		--denominator "PuppiMET_PT_000000","TrackerMET_PT_000000" \
		--title ";Gen. MET (GeV);Trigger efficiency (L1 p_{T} > 150 GeV);" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_045.pdf
	./Execute \
		--label "PuppiMET (150 GeV)","TrackerMET (50 GeV)" \
		--file $(TTbarV10),$(TTbarV10) \
		--numerator "PuppiMET_PT_015000","TrackerMET_PT_005000" \
		--denominator "PuppiMET_PT_000000","TrackerMET_PT_000000" \
		--title ";Gen. MET (GeV);Trigger efficiency (L1 p_{T} > 150, 50 GeV);" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_045b.pdf
	cp V10_*pdf ~/public/html/

V10PlotsPart4: Execute
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJetWide_EtaPT100_000000","PFPhase1JetWide_EtaPT100_000000","TrackerJet_EtaPT100_000000","CaloJetWide_EtaPT100_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 100 GeV)" --xmin -5 --xmax 5 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_033.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJetWide_EtaPT40to100_000000","PFPhase1JetWide_EtaPT40to100_000000","TrackerJet_EtaPT40to100_000000","CaloJetWide_EtaPT40to100_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} = 40-100 GeV)" --xmin -5 --xmax 5 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_034.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJet_PTEta15_000000","PFPhase1Jet_PTEta15_000000","TrackerJet_PTEta15_000000","CaloJet_PTEta15_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (barrel)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_035.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJet_PTEtaLarge_000000","PFPhase1Jet_PTEtaLarge_000000","TrackerJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (endcap)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_036.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJetForward_PT_000000","PFPhase1JetForward_PT_000000","TrackerJetForward_PT_000000","CaloJetFoward_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. p_{T} (GeV);Matching efficiency (|eta| > 2.4)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_037.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJet_PTEta15_005000","PFPhase1Jet_PTEta15_005000","TrackerJet_PTEta15_005000","CaloJet_PTEta15_005000" \
		--denominator "PuppiJet_PTEta15_000000","PFPhase1Jet_PTEta15_000000","TrackerJet_PTEta15_000000","CaloJet_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 50 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_038.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJet_PTEtaLarge_005000","PFPhase1Jet_PTEtaLarge_005000","TrackerJet_PTEtaLarge_005000","CaloJet_PTEtaLarge_005000" \
		--denominator "PuppiJet_PTEtaLarge_000000","PFPhase1Jet_PTEtaLarge_000000","TrackerJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 50 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_039.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJetForward_PT_005000","PFPhase1JetForward_PT_005000","TrackerJetForward_PT_005000","CaloJetFoward_PT_005000" \
		--denominator "PuppiJetForward_PT_000000","PFPhase1JetForward_PT_000000","TrackerJetForward_PT_000000","CaloJetFoward_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (|#eta| > 2.4, L1 p_{T} > 50 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_040.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJet_PTEta15_012000","PFPhase1Jet_PTEta15_012000","TrackerJet_PTEta15_012000","CaloJet_PTEta15_012000" \
		--denominator "PuppiJet_PTEta15_000000","PFPhase1Jet_PTEta15_000000","TrackerJet_PTEta15_000000","CaloJet_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (barrel, L1 p_{T} > 120 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_041.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJet_PTEtaLarge_012000","PFPhase1Jet_PTEtaLarge_012000","TrackerJet_PTEtaLarge_012000","CaloJet_PTEtaLarge_012000" \
		--denominator "PuppiJet_PTEtaLarge_000000","PFPhase1Jet_PTEtaLarge_000000","TrackerJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (endcap, L1 p_{T} > 120 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_042.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJetForward_PT_012000","PFPhase1JetForward_PT_012000","TrackerJetForward_PT_012000","CaloJetFoward_PT_012000" \
		--denominator "PuppiJetForward_PT_000000","PFPhase1JetForward_PT_000000","TrackerJetForward_PT_000000","CaloJetFoward_PT_000000" \
		--title ";Gen. p_{T} (GeV);Trigger efficiency (|#eta| > 2.4, L1 p_{T} > 120 GeV)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_043.pdf
	./Execute \
		--label "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiHT_PT_035000","PFPhase1HT_PT_035000","TrackerHT_PT_035000","CaloHT_PT_035000" \
		--denominator "PuppiHT_PT_000000","PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 350 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_044.pdf
	./Execute \
		--label "PuppiHT","TrackerHT","CaloHT" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PFPhase1HT_PT_035000","TrackerHT_PT_035000","CaloHT_PT_035000" \
		--denominator "PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 350 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_044YesPhase1HT.pdf
	./Execute \
		--label "PuppiHT (350)","TrackerHT (200)","CaloHT (350)" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PFPhase1HT_PT_035000","TrackerHT_PT_020000","CaloHT_PT_035000" \
		--denominator "PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 200/350 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_044LowYesPhase1HT.pdf
	./Execute \
		--label "PuppiHT","PuppiPhase1HT","TrackerHT","CaloHT" \
		--file $(HadronicTTbarV10),$(HadronicTTbarV10),$(HadronicTTbarV10),$(HadronicTTbarV10) \
		--numerator "PuppiHT_PT_035000","PFPhase1HT_PT_035000","TrackerHT_PT_035000","CaloHT_PT_035000" \
		--denominator "PuppiHT_PT_000000","PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 350 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_045.pdf
	./Execute \
		--label "PuppiHT","TrackerHT","CaloHT" \
		--file $(HadronicTTbarV10),$(HadronicTTbarV10),$(HadronicTTbarV10) \
		--numerator "PFPhase1HT_PT_035000","TrackerHT_PT_035000","CaloHT_PT_035000" \
		--denominator "PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 350 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_045YesPhase1HT.pdf
	./Execute \
		--label "PuppiHT (350)","PuppiPhase1HT (350)","TrackerHT (200)","CaloHT (350)" \
		--file $(HadronicTTbarV10),$(HadronicTTbarV10),$(HadronicTTbarV10),$(HadronicTTbarV10) \
		--numerator "PuppiHT_PT_035000","PFPhase1HT_PT_035000","TrackerHT_PT_020000","CaloHT_PT_035000" \
		--denominator "PuppiHT_PT_000000","PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 200/350 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_045Low.pdf
	./Execute \
		--label "PuppiHT (350)","TrackerHT (200)","CaloHT (350)" \
		--file $(HadronicTTbarV10),$(HadronicTTbarV10),$(HadronicTTbarV10) \
		--numerator "PFPhase1HT_PT_035000","TrackerHT_PT_020000","CaloHT_PT_035000" \
		--denominator "PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency (L1 p_{T} > 200/350 GeV)" --xmin 0 --xmax 750 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10TTbar_045LowYesPhase1HT.pdf

V10PlotsPart5: Execute
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonIso_EtaPT15_000000","StandaloneDisplacedMuonIso_EtaPT15_000000","StandaloneDisplacedMuonIso_EtaPT15_000000","StandaloneDisplacedMuonIso_EtaPT15_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 15 GeV)" --xmin -3 --xmax 3 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_046.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonDXYIso_EtaPT15_000000","StandaloneDisplacedMuonDXYIso_EtaPT15_000000","StandaloneDisplacedMuonDXYIso_EtaPT15_000000","StandaloneDisplacedMuonDXYIso_EtaPT15_000000" \
		--denominator "StandaloneDisplacedMuonIsoNoMatch_EtaPT15_000000","StandaloneDisplacedMuonIsoNoMatch_EtaPT15_000000","StandaloneDisplacedMuonIsoNoMatch_EtaPT15_000000","StandaloneDisplacedMuonIsoNoMatch_EtaPT15_000000" \
		--title ";Gen. #eta;Matching efficiency (p_{T} > 15 GeV, d_{XY} > 0)" --xmin -3 --xmax 3 --ymin 0.00 --ymax 1.10 --rebin 1 \
		--Davignon $(Davignon) --output V10_047.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonIsoBEta_PT_000000","StandaloneDisplacedMuonIsoBEta_PT_000000","StandaloneDisplacedMuonIsoBEta_PT_000000","StandaloneDisplacedMuonIsoBEta_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. p_{T};Matching efficiency (barrel)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_048.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonDXYIsoBEta_PT_000000","StandaloneDisplacedMuonDXYIsoBEta_PT_000000","StandaloneDisplacedMuonDXYIsoBEta_PT_000000","StandaloneDisplacedMuonDXYIsoBEta_PT_000000" \
		--denominator "StandaloneDisplacedMuonIsoBEtaNoMatch_PT_000000","StandaloneDisplacedMuonIsoBEtaNoMatch_PT_000000","StandaloneDisplacedMuonIsoBEtaNoMatch_PT_000000","StandaloneDisplacedMuonIsoBEtaNoMatch_PT_000000" \
		--title ";Gen. p_{T};Matching efficiency (barrel, d_{XY} > 0)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_049.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonIsoOEta_PT_000000","StandaloneDisplacedMuonIsoOEta_PT_000000","StandaloneDisplacedMuonIsoOEta_PT_000000","StandaloneDisplacedMuonIsoOEta_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. p_{T};Matching efficiency (overlap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_050.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonDXYIsoOEta_PT_000000","StandaloneDisplacedMuonDXYIsoOEta_PT_000000","StandaloneDisplacedMuonDXYIsoOEta_PT_000000","StandaloneDisplacedMuonDXYIsoOEta_PT_000000" \
		--denominator "StandaloneDisplacedMuonIsoOEtaNoMatch_PT_000000","StandaloneDisplacedMuonIsoOEtaNoMatch_PT_000000","StandaloneDisplacedMuonIsoOEtaNoMatch_PT_000000","StandaloneDisplacedMuonIsoOEtaNoMatch_PT_000000" \
		--title ";Gen. p_{T};Matching efficiency (overlap, d_{XY} > 0)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_051.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonIsoEEta_PT_000000","StandaloneDisplacedMuonIsoEEta_PT_000000","StandaloneDisplacedMuonIsoEEta_PT_000000","StandaloneDisplacedMuonIsoEEta_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. p_{T};Matching efficiency (endcap)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_052.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonDXYIsoEEta_PT_000000","StandaloneDisplacedMuonDXYIsoEEta_PT_000000","StandaloneDisplacedMuonDXYIsoEEta_PT_000000","StandaloneDisplacedMuonDXYIsoEEta_PT_000000" \
		--denominator "StandaloneDisplacedMuonIsoEEtaNoMatch_PT_000000","StandaloneDisplacedMuonIsoEEtaNoMatch_PT_000000","StandaloneDisplacedMuonIsoEEtaNoMatch_PT_000000","StandaloneDisplacedMuonIsoEEtaNoMatch_PT_000000" \
		--title ";Gen. p_{T};Matching efficiency (endcap, d_{XY} > 0)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_053.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonIsoB_PT_001500","StandaloneDisplacedMuonIsoB_PT_001500","StandaloneDisplacedMuonIsoB_PT_001500","StandaloneDisplacedMuonIsoB_PT_001500" \
		--denominator "StandaloneDisplacedMuonIsoB_PT_000000","StandaloneDisplacedMuonIsoB_PT_000000","StandaloneDisplacedMuonIsoB_PT_000000","StandaloneDisplacedMuonIsoB_PT_000000" \
		--title ";Gen. p_{T};Trigger efficiency (barrel, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_054.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonIsoO_PT_001500","StandaloneDisplacedMuonIsoO_PT_001500","StandaloneDisplacedMuonIsoO_PT_001500","StandaloneDisplacedMuonIsoO_PT_001500" \
		--denominator "StandaloneDisplacedMuonIsoO_PT_000000","StandaloneDisplacedMuonIsoO_PT_000000","StandaloneDisplacedMuonIsoO_PT_000000","StandaloneDisplacedMuonIsoO_PT_000000" \
		--title ";Gen. p_{T};Trigger efficiency (overlap, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_055.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonIsoE_PT_001500","StandaloneDisplacedMuonIsoE_PT_001500","StandaloneDisplacedMuonIsoE_PT_001500","StandaloneDisplacedMuonIsoE_PT_001500" \
		--denominator "StandaloneDisplacedMuonIsoE_PT_000000","StandaloneDisplacedMuonIsoE_PT_000000","StandaloneDisplacedMuonIsoE_PT_000000","StandaloneDisplacedMuonIsoE_PT_000000" \
		--title ";Gen. p_{T};Trigger efficiency (endcap, p_{T} > 15 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_056.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonIso_DXYPT15_000000","StandaloneDisplacedMuonIso_DXYPT15_000000","StandaloneDisplacedMuonIso_DXYPT15_000000","StandaloneDisplacedMuonIso_DXYPT15_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";Gen. d_{XY};Matching efficiency (p_{T} > 15 GeV)" --xmin 0 --xmax 300 --ymin 0.00 --ymax 1.10 --rebin 3 \
		--Davignon $(Davignon) --output V10_057.pdf
	./Execute \
		--label "c#tau = 1","c#tau = 10","c#tau = 100","c#tau = 1000" \
		--file $(DarkSUSYCT1V10),$(DarkSUSYCT10V10),$(DarkSUSYCT100V10),$(DarkSUSYCT1000V10) \
		--numerator "StandaloneDisplacedMuonDXYIso_DXYPT15_000000","StandaloneDisplacedMuonDXYIso_DXYPT15_000000","StandaloneDisplacedMuonDXYIso_DXYPT15_000000","StandaloneDisplacedMuonDXYIso_DXYPT15_000000" \
		--denominator "StandaloneDisplacedMuonIsoNoMatch_DXYPT15_000000","StandaloneDisplacedMuonIsoNoMatch_DXYPT15_000000","StandaloneDisplacedMuonIsoNoMatch_DXYPT15_000000","StandaloneDisplacedMuonIsoNoMatch_DXYPT15_000000" \
		--title ";Gen. d_{XY};Matching efficiency (p_{T} > 15 GeV, d_{XY} > 0)" --xmin 0 --xmax 300 --ymin 0.00 --ymax 1.10 --rebin 3 \
		--Davignon $(Davignon) --output V10_058.pdf
	cp V10*pdf ~/public/html/

V10PlotsPart6: Execute
	./Execute \
		--label "Standalone","Displaced","Displaced (L1 D_{XY} > 0)","Displaced (L_{xy} < 1m)","Displaced (L_{xy} < 1m & L1 D_{XY} > 0)" \
		--file $(DisplacedMuonV10),$(DisplacedMuonV10),$(DisplacedMuonV10),$(DisplacedMuonV10),$(DisplacedMuonV10) \
		--numerator "StandaloneMuonIsoBEta_DXYPT20_001000","StandaloneDisplacedMuonIsoBEta_DXYPT20_001000","StandaloneDisplacedMuonIsoDXYBEta_DXYPT20_001000","StandaloneDisplacedMuonLxy1000IsoBEta_DXYPT20_001000","StandaloneDisplacedMuonLxy1000IsoDXYBEta_DXYPT20_001000" \
		--denominator "StandaloneMuonIsoBEtaNoMatch_DXYPT20_000000","StandaloneDisplacedMuonIsoBEtaNoMatch_DXYPT20_000000","StandaloneDisplacedMuonIsoDXYBEtaNoMatch_DXYPT20_000000","StandaloneDisplacedMuonLxy1000IsoBEtaNoMatch_DXYPT20_000000","StandaloneDisplacedMuonLxy1000IsoDXYBEtaNoMatch_DXYPT20_000000" \
		--title ";Gen. d_{XY} (cm);Matching efficiency (Gen. p_{T} > 20 GeV, L1 p_{T} > 10 GeV)" --xmin 0 --xmax 150 --ymin 0.00 --ymax 1.10 --rebin 10 \
		--legendx 0.35 --legendy 0.50 \
		--Davignon $(Davignon) --output V10_059.pdf
	cp V10*pdf ~/public/html/

V10PlotsPart7: Execute
	./Execute \
		--label "PuppiJet (120 GeV)","PuppiPhase1Jet (120 GeV)","TkJet (70 GeV)","CaloJet (130 GeV)" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJet_PTEta15_012000","PFPhase1Jet_PTEta15_012000","TrackerJet_PTEta15_007000","CaloJet_PTEta15_013000" \
		--denominator "PuppiJetNoMatch_PTEta15_000000","PFPhase1JetNoMatch_PTEta15_000000","TrackerJetNoMatch_PTEta15_000000","CaloJetNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (barrel)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_100.pdf
	./Execute \
		--label "PuppiJet (120 GeV)","TkJet (70 GeV)","CaloJet (130 GeV)" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PFPhase1Jet_PTEta15_012000","TrackerJet_PTEta15_007000","CaloJet_PTEta15_013000" \
		--denominator "PFPhase1JetNoMatch_PTEta15_000000","TrackerJetNoMatch_PTEta15_000000","CaloJetNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.45 --legendy 0.20 \
		--text 0.50,0.40,"Barrel |#eta| < 1.5" \
		--marker 20,21,22 \
		--Davignon $(Davignon) --output V10_100YesPhase1HT.pdf
	./Execute \
		--label "PuppiJet (120 GeV)","PuppiPhase1Jet (120 GeV)","TkJet (70 GeV)","CaloJet (130 GeV)" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJet_PTEtaLarge_012000","PFPhase1Jet_PTEtaLarge_012000","TrackerJet_PTEtaLarge_007000","CaloJet_PTEtaLarge_013000" \
		--denominator "PuppiJetNoMatch_PTEtaLarge_000000","PFPhase1JetNoMatch_PTEtaLarge_000000","TrackerJetNoMatch_PTEtaLarge_000000","CaloJetNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (endcap)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_101.pdf
	./Execute \
		--label "PuppiJet (120 GeV)","TkJet (70 GeV)","CaloJet (130 GeV)" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PFPhase1Jet_PTEtaLarge_012000","TrackerJet_PTEtaLarge_007000","CaloJet_PTEtaLarge_013000" \
		--denominator "PFPhase1JetNoMatch_PTEtaLarge_000000","TrackerJetNoMatch_PTEtaLarge_000000","CaloJetNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.45 --legendy 0.20 \
		--text 0.50,0.40,"Endcap 1.5 < |#eta| < 2.4" \
		--marker 20,21,22 \
		--Davignon $(Davignon) --output V10_101YesPhase1HT.pdf
	./Execute \
		--label "PuppiJet (120 GeV)","PuppiPhase1Jet (120 GeV)","CaloJet (130 GeV)" \
		--file $(TTbarV10),$(TTbarV10),$(TTbarV10) \
		--numerator "PuppiJetForward_PT_012000","PFPhase1JetForward_PT_012000","CaloJetFoward_PT_013000" \
		--denominator "PuppiJetForwardNoMatch_PT_000000","PFPhase1JetForwardNoMatch_PT_000000","CaloJetFowardNoMatch_PT_000000" \
		--color -1,-2,-4 \
		--title ";Gen. p_{T} (GeV);Combined efficiency (|#eta| > 2.4)" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_102.pdf
	./Execute \
		--label "PuppiJet (120 GeV)","CaloJet (130 GeV)" \
		--file $(TTbarV10),$(TTbarV10) \
		--numerator "PFPhase1JetForward_PT_012000","CaloJetFoward_PT_013000" \
		--denominator "PFPhase1JetForwardNoMatch_PT_000000","CaloJetFowardNoMatch_PT_000000" \
		--color -1,-3 \
		--title ";Gen. p_{T} (GeV);Combined efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.45 --legendy 0.20 \
		--text 0.50,0.40,"Forward |#eta| > 2.4" \
		--marker 20,22 \
		--Davignon $(Davignon) --output V10_102YesPhase1HT.pdf
	./Execute \
		--label "PuppiHT (326 GeV)","PuppiPhase1HT (326 GeV)","TrackerHT (184 GeV)","CaloHT (450 GeV)" \
		--file $(QCDV10),$(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PuppiHT_PT_032600","PFPhase1HT_PT_032600","TrackerHT_PT_018400","CaloHT_PT_045000" \
		--denominator "PuppiHT_PT_000000","PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency" --xmin 0 --xmax 1000 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.40 --legendy 0.20 \
		--Davignon $(Davignon) --output V10_103.pdf
	./Execute \
		--label "PuppiHT (370 GeV)","TrackerHT (200 GeV)","CaloHT (650 GeV)" \
		--file $(QCDV10),$(QCDV10),$(QCDV10) \
		--numerator "PFPhase1HT_PT_037000","TrackerHT_PT_02000","CaloHT_PT_065000" \
		--denominator "PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency" --xmin 0 --xmax 1200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.50 --legendy 0.20 \
		--Davignon $(Davignon) --output V10_103YesPhase1HT.pdf
	./Execute \
		--label "PuppiHT (326 GeV)","PuppiPhase1HT (326 GeV)","TrackerHT (184 GeV)","CaloHT (450 GeV)" \
		--file $(HadronicTTbarV10),$(HadronicTTbarV10),$(HadronicTTbarV10),$(HadronicTTbarV10) \
		--numerator "PuppiHT_PT_032600","PFPhase1HT_PT_032600","TrackerHT_PT_018400","CaloHT_PT_045000" \
		--denominator "PuppiHT_PT_000000","PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency" --xmin 0 --xmax 1000 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.40 --legendy 0.20 \
		--Davignon $(Davignon) --output V10HadTTbar_103.pdf
	./Execute \
		--label "PuppiHT (370 GeV)","TrackerHT (200 GeV)","CaloHT (650 GeV)" \
		--file $(HadronicTTbarV10),$(HadronicTTbarV10),$(HadronicTTbarV10) \
		--numerator "PFPhase1HT_PT_037000","TrackerHT_PT_020000","CaloHT_PT_065000" \
		--denominator "PFPhase1HT_PT_000000","TrackerHT_PT_000000","CaloHT_PT_000000" \
		--title ";Gen. H_{T} (GeV);Trigger efficiency" --xmin 0 --xmax 1200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.50 --legendy 0.20 \
		--Davignon $(Davignon) --output V10HadTTbar_103YesPhase1HT.pdf
	./Execute \
		--label "PuppiMET (112 GeV)","TrackerMET (82 GeV)" \
		--file $(VBFHInvV10),$(VBFHInvV10) \
		--numerator "PuppiMET_PT_011200","TrackerMET_PT_008200" \
		--denominator "PuppiMET_PT_000000","TrackerMET_PT_000000" \
		--title ";Gen. MET (GeV);Trigger efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.45 --legendy 0.20 \
		--Davignon $(Davignon) --output V10_104.pdf
	./Execute \
		--label "PuppiMET (112 GeV)","TrackerMET (82 GeV)" \
		--file $(TTbarV10),$(TTbarV10) \
		--numerator "PuppiMET_PT_011200","TrackerMET_PT_008200" \
		--denominator "PuppiMET_PT_000000","TrackerMET_PT_000000" \
		--title ";Gen. MET (GeV);Trigger efficiency" --xmin 0 --xmax 500 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--legendx 0.45 --legendy 0.20 \
		--Davignon $(Davignon) --output V10TTbar_104.pdf
	./Execute \
		--label "HPSPFTau1 (Medium) (46 GeV)","NNPuppiTau (Loose) (36 GeV)","tkEGTau (35 GeV)","CaloTau (58 TeV)" \
		--file $(HTauTauV10),$(HTauTauV10),$(HTauTauV10),$(HTauTauV10) \
		--numerator "PFIsoTau_PTEta15_004600","NNTauLooseIso_PTEta15_003600","TkEGTauIso_PTEta15_003500","CaloTauIso_PTEta15_005800" \
		--denominator "PFIsoTauNoMatch_PTEta15_000000","NNTauLooseIsoNoMatch_PTEta15_000000","TkEGTauIsoNoMatch_PTEta15_000000","CaloTauIsoNoMatch_PTEta15_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (barrel)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_105.pdf
	./Execute \
		--label "HPSPFTau1 (Medium) (46 GeV)","NNPuppiTau (Loose) (36 GeV)","tkEGTau (35 GeV)","CaloTau (58 GeV)" \
		--file $(HTauTauV10),$(HTauTauV10),$(HTauTauV10),$(HTauTauV10) \
		--numerator "PFIsoTau_PTEtaLarge_004600","NNTauLooseIso_PTEtaLarge_003600","TkEGTauIso_PTEtaLarge_003500","CaloTauIso_PTEtaLarge_005800" \
		--denominator "PFIsoTauNoMatch_PTEtaLarge_000000","NNTauLooseIsoNoMatch_PTEtaLarge_000000","TkEGTauIsoNoMatch_PTEtaLarge_000000","CaloTauIsoNoMatch_PTEtaLarge_000000" \
		--title ";Gen. p_{T} (GeV);Combined efficiency (endcap)" --xmin 0 --xmax 200 --ymin 0.00 --ymax 1.10 --rebin 2 \
		--Davignon $(Davignon) --output V10_106.pdf
	cp V10*pdf ~/public/html

V10LDRPlots: Execute
	./Execute \
		--label "EG Electron","EG Electron (PT > 10)","EG Photon","EG Photon (PT > 10)" \
		--file $(DYLLLDRV10),$(DYLLLDRV10),$(HGGLDRV10),$(HGGLDRV10) \
		--numerator "EGLDR_DR_000000","EGLDR_DRPT10_000000","EGTrackIDLDR_DR_000000","EGTrackIDLDR_DRPT10_000000" \
		--denominator "simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.60 --line 0 --output V10LDR_001.pdf
	./Execute \
		--label "TkElectron","TkElectron (PT > 10)","TkPhoton","TkPhoton (PT > 10)" \
		--file $(DYLLLDRV10),$(DYLLLDRV10),$(HGGLDRV10),$(HGGLDRV10) \
		--numerator "TkElectronLDR_DR_000000","TkElectronLDR_DRPT10_000000","TkPhotonTrackIDLDR_DR_000000","TkPhotonTrackIDLDR_DRPT10_000000" \
		--denominator "simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.60 --line 0 --output V10LDR_002.pdf
	./Execute \
		--label "STAMuon","STAMuon (PT > 10)","TkMuon","TkMuon (PT > 10)","TkMuonStub","TkMuonStub (PT > 10)" \
		--file $(DYLLLDRV10),$(DYLLLDRV10),$(DYLLLDRV10),$(DYLLLDRV10),$(DYLLLDRV10),$(DYLLLDRV10) \
		--numerator "StandaloneMuonLDR_DR_000000","StandaloneMuonLDR_DRPT10_000000","TkMuonLDR_DR_000000","TkMuonLDR_DRPT10_000000","TkMuonStubLDR_DR_000000","TkMuonStubLDR_DRPT10_000000" \
		--denominator "simple","simple","simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.001 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V10LDR_003.pdf
	./Execute \
		--label "HPSPFTau_1","NNTau","HPSPFTau_2" \
		--file $(HTauTauLDRV10),$(HTauTauLDRV10),$(HTauTauLDRV10) \
		--numerator "PFTauLDR_DR_000000","NNTauLDR_DR_000000","HPSTauLDR_DR_000000" \
		--denominator "simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.005 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V10LDR_004.pdf
	./Execute \
		--label "HPSPFTau_1","NNTau","HPSPFTau_2" \
		--file $(HTauTauLDRV10),$(HTauTauLDRV10),$(HTauTauLDRV10) \
		--numerator "PFTauLDR_DRPT50_000000","NNTauLDR_DRPT50_000000","HPSTauLDR_DRPT50_000000" \
		--denominator "simple","simple","simple" \
		--title ";#DeltaR (Gen p_{T} > 50 GeV);a.u." --xmin 0 --xmax 1 --ymin 0.005 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V10LDR_004b.pdf
	./Execute \
		--label "tkEGTau","tkEGTau (PT > 10)","CaloTau","CaloTau (PT > 10)","tkCaloTau","tkCaloTau (PT > 10)" \
		--file $(HTauTauLDRV10),$(HTauTauLDRV10),$(HTauTauLDRV10),$(HTauTauLDRV10),$(HTauTauLDRV10),$(HTauTauLDRV10) \
		--numerator "TkEGTauLDR_DR_000000","TkEGTauLDR_DRPT10_000000","CaloTauLDR_DR_000000","CaloTauLDR_DRPT10_000000","CaloTkTauLDR_DR_000000","CaloTkTauLDR_DRPT10_000000" \
		--denominator "simple","simple","simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.01 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V10LDR_005.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDLDRV10),$(QCDLDRV10),$(QCDLDRV10),$(QCDLDRV10) \
		--numerator "PuppiJetLDR_DR_000000","PFPhase1JetLDR_DR_000000","TrackerJetWideLDR_DR_000000","CaloJetWideLDR_DR_000000" \
		--denominator "simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.01 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V10LDR_006.pdf
	./Execute \
		--label "PuppiJet","PuppiPhase1Jet","TkJet","CaloJet" \
		--file $(QCDLDRV10),$(QCDLDRV10),$(QCDLDRV10),$(QCDLDRV10) \
		--numerator "PuppiJetLDR_DRPT10_000000","PFPhase1JetLDR_DRPT10_000000","TrackerJetWideLDR_DRPT10_000000","CaloJetWideLDR_DRPT10_000000" \
		--denominator "simple","simple","simple","simple" \
		--title ";#DeltaR;a.u." --xmin 0 --xmax 1 --ymin 0.01 --ymax 100 --logy true --rebin 2 \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.50 --line 0 --output V10LDR_007.pdf
	cp V10LDR*pdf ~/public/html/

V10IsoPlots: Execute
	./Execute \
		--label "TkElectronV1 (Barrel)","TkElectronV1 (Endcap)" \
		--file $(DYLLV10),$(DYLLV10) \
		--numerator "TkElectronIso_TkIsoPT10Eta15_000000","TkElectronIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.85 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.20 --line 0.982 --output V10Iso_001.pdf
	./Execute \
		--label "TkElectron (Barrel)","TkElectron (Endcap)" \
		--file $(DYLLV10),$(DYLLV10) \
		--numerator "TkElectronV2Iso_TkIsoPT10Eta15_000000","TkElectronV2Iso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.90 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.35 --legendy 0.20 --line 0.982 --output V10Iso_002.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)","TkPhotonPV (Barrel)","TkPhotonPV (Endcap)" \
		--file $(HGGV10),$(HGGV10),$(HGGV10),$(HGGV10) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000","TkPhotonPVTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonPVTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative","cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V10Iso_003.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)","TkPhotonPV (Barrel)","TkPhotonPV (Endcap)" \
		--file $(HGGV10),$(HGGV10),$(HGGV10),$(HGGV10) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000","TkPhotonPVTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonPVTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative","cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0.2 --xmax 0.5 --ymin 0.91 --ymax 0.96 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V10Iso_003a.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)","TkPhotonPV (Barrel)","TkPhotonPV (Endcap)" \
		--file $(HGGV10),$(HGGV10),$(HGGV10),$(HGGV10) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000","TkPhotonPVTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonPVTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative","cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0.05 --xmax 0.07 --ymin 0.92 --ymax 0.96 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V10Iso_003b.pdf
	./Execute \
		--label "TkPhoton (Barrel)","TkPhoton (Endcap)" \
		--file $(HGGV10),$(HGGV10) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0 --xmax 0.5 --ymin 0.80 --ymax 1.00 --grid true \
		--Davignon $(Davignon) --legendx 0.45 --legendy 0.15 --line 0.946 --output V10Iso_003c.pdf
	cp V10Iso*pdf ~/public/html/

LowEnergyElectron: Execute
	./Execute \
		--label "EGElectron (V8.2)","TkElectron (V8.2)","TkIsoElectron (V8.2)" \
		--file DYLL_V8p2.root,DYLL_V8p2.root,DYLL_V8p2.root \
		--numerator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000" \
		--denominator "auto","auto","TkElectronIsoNoMatch_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 40 --output LowEnergyElectron_001.pdf \
		--legendx 0.45 --legendy 0.20
	./Execute \
		--label "EGElectron (V8.2)","TkElectron (V8.2)","TkIsoElectron (V8.2)" \
		--file DYLL_V8p2.root,DYLL_V8p2.root,DYLL_V8p2.root \
		--numerator "EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000" \
		--denominator "auto","auto","TkElectronIsoNoMatch_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 40 --output LowEnergyElectron_002.pdf \
		--legendx 0.45 --legendy 0.20
	./Execute \
		--label "EGElectron (DYLL V8.2)","TkElectron (DYLL V8.2)","TkIsoElectron (DYLL V8.2)" \
		--file DYLL_V8p2.root,DYLL_V8p2.root,DYLL_V8p2.root \
		--numerator "EGTrackIDIso_PTEta15_000900","TkElectronTrackIDIso_PTEta15_000900","TkIsoElectron_PTEta15_000900" \
		--denominator "EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 40 --output LowEnergyElectron_003.pdf --rebin 1
	cp LowEnergyElectron_*pdf ~/public/html/

V9PlotsPart5: Execute
	echo Hello
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)","EGElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "EGTrackIDIso_PTEta15_001500","EGTrackIDIso_PTEta15_001500","EGTrackIDIso_PTEta15_001500","EGTrackIDIso_PTEta15_001500" \
		--denominator "EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_001.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)","EGElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "EGTrackIDIso_PTEtaLarge_001500","EGTrackIDIso_PTEtaLarge_001500","EGTrackIDIso_PTEtaLarge_001500","EGTrackIDIso_PTEtaLarge_001500" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_002.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)","EGElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "EGTrackIDExtendedIso_PT_001500","EGTrackIDExtendedIso_PT_001500","EGTrackIDExtendedIso_PT_001500","EGTrackIDExtendedIso_PT_001500" \
		--denominator "EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_003.pdf --rebin 2
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)","TkElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkElectronTrackIDIso_PTEta15_001500","TkElectronTrackIDIso_PTEta15_001500","TkElectronTrackIDIso_PTEta15_001500","TkElectronTrackIDIso_PTEta15_001500" \
		--denominator "TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_004.pdf --rebin 2
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)","TkElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkElectronTrackIDIso_PTEtaLarge_001500","TkElectronTrackIDIso_PTEtaLarge_001500","TkElectronTrackIDIso_PTEtaLarge_001500","TkElectronTrackIDIso_PTEtaLarge_001500" \
		--denominator "TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_005.pdf --rebin 2
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)","TkIsoElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkIsoElectron_PTEta15_001500","TkIsoElectron_PTEta15_001500","TkIsoElectron_PTEta15_001500","TkIsoElectron_PTEta15_001500" \
		--denominator "TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_006.pdf --rebin 2
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)","TkIsoElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkIsoElectron_PTEtaLarge_001500","TkIsoElectron_PTEtaLarge_001500","TkIsoElectron_PTEtaLarge_001500","TkIsoElectron_PTEtaLarge_001500" \
		--denominator "TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_007.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)","EGElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_008.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)","EGElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_009.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)","EGElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_010.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)","EGElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "EGTrackIDIso_EtaPT15_000000","EGTrackIDIso_EtaPT15_000000","EGTrackIDIso_EtaPT15_000000","EGTrackIDIso_EtaPT15_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output V9P5_011.pdf
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)","TkElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_012.pdf --rebin 2
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)","TkElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_014.pdf --rebin 2
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)","TkElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkElectronTrackIDIso_EtaPT15_000000","TkElectronTrackIDIso_EtaPT15_000000","TkElectronTrackIDIso_EtaPT15_000000","TkElectronTrackIDIso_EtaPT15_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output V9P5_015.pdf
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)","TkIsoElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000" \
		--denominator "TkElectronIsoNoMatch_PTEta15_000000","TkElectronIsoNoMatch_PTEta15_000000","TkElectronIsoNoMatch_PTEta15_000000","TkElectronIsoNoMatch_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_016.pdf --rebin 2
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)","TkIsoElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000" \
		--denominator "TkElectronIsoNoMatch_PTEtaLarge_000000","TkElectronIsoNoMatch_PTEtaLarge_000000","TkElectronIsoNoMatch_PTEtaLarge_000000","TkElectronIsoNoMatch_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P5_017.pdf --rebin 2
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)","TkIsoElectron (DYLL V9.3 NoAging)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V9p3.root \
		--numerator "TkIsoElectron_EtaPT15_000000","TkIsoElectron_EtaPT15_000000","TkIsoElectron_EtaPT15_000000","TkIsoElectron_EtaPT15_000000" \
		--denominator "TkElectronIsoNoMatch_EtaPT15_000000","TkElectronIsoNoMatch_EtaPT15_000000","TkElectronIsoNoMatch_EtaPT15_000000","TkElectronIsoNoMatch_EtaPT15_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output V9P5_018.pdf
	cp V9P5*pdf ~/public/html/

V9PlotsPart4: Execute
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V8.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V8.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "PuppiJet_PT_000000","PuppiJet_PT_000000","PuppiJet_PT_000000","CaloJet_PT_000000","CaloJet_PT_000000","CaloJet_PT_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output V9P4_001.pdf --rebin 2
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V8.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V8.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "PuppiJetWide_EtaPT100_000000","PuppiJetWide_EtaPT100_000000","PuppiJetWide_EtaPT100_000000","CaloJetWide_EtaPT100_000000","CaloJetWide_EtaPT100_000000","CaloJetWide_EtaPT100_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -5.2 --xmax 5.2 --output V9P4_002.pdf --rebin 1
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V8.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V8.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "PuppiJet_PTEta15_000000","PuppiJet_PTEta15_000000","PuppiJet_PTEta15_000000","CaloJet_PTEta15_000000","CaloJet_PTEta15_000000","CaloJet_PTEta15_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output V9P4_003.pdf --rebin 2
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V8.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V8.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "PuppiJet_PTEtaLarge_000000","PuppiJet_PTEtaLarge_000000","PuppiJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output V9P4_004.pdf --rebin 2
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V8.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V8.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "PuppiJetForward_PT_000000","PuppiJetForward_PT_000000","PuppiJetForward_PT_000000","CaloJetFoward_PT_000000","CaloJetFoward_PT_000000","CaloJetFoward_PT_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output V9P4_005.pdf --rebin 2
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V8.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V8.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "PuppiJetWide_EtaPT30_000000","PuppiJetWide_EtaPT30_000000","PuppiJetWide_EtaPT30_000000","CaloJetWide_EtaPT30_000000","CaloJetWide_EtaPT30_000000","CaloJetWide_EtaPT30_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -5.2 --xmax 5.2 --output V9P4_006.pdf --rebin 1
	cp V9P4_*pdf ~/public/html/

V9PlotsPart3: Execute
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "EGTrackIDIso_PTEta15_001500","EGTrackIDIso_PTEta15_001500","EGTrackIDIso_PTEta15_001500" \
		--denominator "EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_001.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "EGTrackIDIso_PTEtaLarge_001500","EGTrackIDIso_PTEtaLarge_001500","EGTrackIDIso_PTEtaLarge_001500" \
		--denominator "EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_002.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "EGTrackIDExtendedIso_PT_001500","EGTrackIDExtendedIso_PT_001500","EGTrackIDExtendedIso_PT_001500" \
		--denominator "EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_003.pdf --rebin 2
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkElectronTrackIDIso_PTEta15_001500","TkElectronTrackIDIso_PTEta15_001500","TkElectronTrackIDIso_PTEta15_001500" \
		--denominator "TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_004.pdf --rebin 2
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkElectronTrackIDIso_PTEtaLarge_001500","TkElectronTrackIDIso_PTEtaLarge_001500","TkElectronTrackIDIso_PTEtaLarge_001500" \
		--denominator "TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_005.pdf --rebin 2
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkIsoElectron_PTEta15_001500","TkIsoElectron_PTEta15_001500","TkIsoElectron_PTEta15_001500" \
		--denominator "TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_006.pdf --rebin 2
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkIsoElectron_PTEtaLarge_001500","TkIsoElectron_PTEtaLarge_001500","TkIsoElectron_PTEtaLarge_001500" \
		--denominator "TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_007.pdf --rebin 2
	./Execute \
		--label "Muon (DYLL V7.5.2) missing","Muon (DYLL V8.2)","Muon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "StandaloneMuonIsoBarrel_PT_000000","StandaloneMuonIsoBarrel_PT_000000","StandaloneMuonIsoBarrel_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_008.pdf --rebin 2
	./Execute \
		--label "Muon (DYLL V7.5.2) missing","Muon (DYLL V8.2)","Muon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "StandaloneMuonIsoEndcap_PT_000000","StandaloneMuonIsoEndcap_PT_000000","StandaloneMuonIsoEndcap_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_009.pdf --rebin 2
	./Execute \
		--label "Muon (DYLL V7.5.2)","Muon (DYLL V8.2)","Muon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "StandaloneMuonIso_EtaPT15_000000","StandaloneMuonIso_EtaPT15_000000","StandaloneMuonIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output V9P3_010.pdf --rebin 1
	./Execute \
		--label "Muon (DYLL V7.5.2) missing","Muon (DYLL V8.2)","Muon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "StandaloneMuonIsoB_PT_001500","StandaloneMuonIsoB_PT_001500","StandaloneMuonIsoB_PT_001500" \
		--denominator "StandaloneMuonIsoB_PT_000000","StandaloneMuonIsoB_PT_000000","StandaloneMuonIsoB_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_015.pdf --rebin 2
	./Execute \
		--label "Muon (DYLL V7.5.2) missing","Muon (DYLL V8.2)","Muon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "StandaloneMuonIsoO_PT_001500","StandaloneMuonIsoO_PT_001500","StandaloneMuonIsoO_PT_001500" \
		--denominator "StandaloneMuonIsoO_PT_000000","StandaloneMuonIsoO_PT_000000","StandaloneMuonIsoO_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_016.pdf --rebin 2
	./Execute \
		--label "Muon (DYLL V7.5.2) missing","Muon (DYLL V8.2)","Muon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "StandaloneMuonIsoE_PT_001500","StandaloneMuonIsoE_PT_001500","StandaloneMuonIsoE_PT_001500" \
		--denominator "StandaloneMuonIsoE_PT_000000","StandaloneMuonIsoE_PT_000000","StandaloneMuonIsoE_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_017.pdf --rebin 2
	./Execute \
		--label "TkMuon (DYLL V7.5.2) missing","TkMuon (DYLL V8.2)","TkMuon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkMuonIsoBarrel_PT_000000","TkMuonIsoBarrel_PT_000000","TkMuonIsoBarrel_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_018.pdf --rebin 2
	./Execute \
		--label "TkMuon (DYLL V7.5.2) missing","TkMuon (DYLL V8.2)","TkMuon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkMuonIsoEndcap_PT_000000","TkMuonIsoEndcap_PT_000000","TkMuonIsoEndcap_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_019.pdf --rebin 2
	./Execute \
		--label "TkMuon (DYLL V7.5.2)","TkMuon (DYLL V8.2)","TkMuon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkMuonIso_EtaPT15_000000","TkMuonIso_EtaPT15_000000","TkMuonIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output V9P3_020.pdf --rebin 1
	./Execute \
		--label "TkMuon (DYLL V7.5.2) missing","TkMuon (DYLL V8.2)","TkMuon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkMuonIsoB_PT_001500","TkMuonIsoB_PT_001500","TkMuonIsoB_PT_001500" \
		--denominator "TkMuonIsoB_PT_000000","TkMuonIsoB_PT_000000","TkMuonIsoB_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_024.pdf --rebin 2
	./Execute \
		--label "TkMuon (DYLL V7.5.2) missing","TkMuon (DYLL V8.2)","TkMuon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkMuonIsoO_PT_001500","TkMuonIsoO_PT_001500","TkMuonIsoO_PT_001500" \
		--denominator "TkMuonIsoO_PT_000000","TkMuonIsoO_PT_000000","TkMuonIsoO_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_025.pdf --rebin 2
	./Execute \
		--label "TkMuon (DYLL V7.5.2) missing","TkMuon (DYLL V8.2)","TkMuon (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkMuonIsoE_PT_001500","TkMuonIsoE_PT_001500","TkMuonIsoE_PT_001500" \
		--denominator "TkMuonIsoE_PT_000000","TkMuonIsoE_PT_000000","TkMuonIsoE_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P3_026.pdf --rebin 2
	cp V9P3*pdf ~/public/html/

V9PlotsPart2: Execute
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P2_001.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P2_002.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P2_003.pdf --rebin 2
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V8.2)","EGElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "EGTrackIDIso_EtaPT15_000000","EGTrackIDIso_EtaPT15_000000","EGTrackIDIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output V9P2_004.pdf
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P2_005.pdf --rebin 2
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P2_006.pdf --rebin 2
	./Execute \
		--label "TkElectron (DYLL V7.5.2)","TkElectron (DYLL V8.2)","TkElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkElectronTrackIDIso_EtaPT15_000000","TkElectronTrackIDIso_EtaPT15_000000","TkElectronTrackIDIso_EtaPT15_000000" \
		--denominator "auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output V9P2_007.pdf
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000" \
		--denominator "TkElectronIsoNoMatch_PTEta15_000000","TkElectronIsoNoMatch_PTEta15_000000","TkElectronIsoNoMatch_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P2_008.pdf --rebin 2
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000" \
		--denominator "TkElectronIsoNoMatch_PTEtaLarge_000000","TkElectronIsoNoMatch_PTEtaLarge_000000","TkElectronIsoNoMatch_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9P2_009.pdf --rebin 2
	./Execute \
		--label "TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V8.2)","TkIsoElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V8p2.root,DYLL_V9.root \
		--numerator "TkIsoElectron_EtaPT15_000000","TkIsoElectron_EtaPT15_000000","TkIsoElectron_EtaPT15_000000" \
		--denominator "TkElectronIsoNoMatch_EtaPT15_000000","TkElectronIsoNoMatch_EtaPT15_000000","TkElectronIsoNoMatch_EtaPT15_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output V9P2_010.pdf
	cp V9P2*pdf ~/public/html/

V9Plots: Execute
	./Execute \
		--label "Threshold 100 GeV","Threshold 150 GeV" \
		--file QCD_V9.root,QCD_V9.root \
		--numerator "CaloJet_PT_010000","CaloJet_PT_015000" \
		--denominator "CaloJet_PT_000000","CaloJet_PT_000000" \
		--title ";Gen p_{T};Efficiency" --xmin 0 --xmax 500 --output V9_001.pdf
	./Execute \
		--label "Threshold 100 GeV","Threshold 150 GeV" \
		--file QCD_V9.root,QCD_V9.root \
		--numerator "PuppiJet_PT_010000","PuppiJet_PT_015000" \
		--denominator "PuppiJet_PT_000000","PuppiJet_PT_000000" \
		--title ";Gen p_{T};Efficiency" --xmin 0 --xmax 500 --output V9_002.pdf
	./Execute \
		--label "PFJet (QCD V7.4.2)","PFJet (QCD V9)","CaloJet (QCD V7.4.2)","CaloJet (QCD V9)" \
		--file QCD_V7p42.root,QCD_V9.root,QCD_V7p42.root,QCD_V9.root \
		--numerator "PuppiJet_PT_000000","PuppiJet_PT_000000","CaloJet_PT_000000","CaloJet_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output V9_003.pdf
	./Execute \
		--label "PFJet (QCD V7.4.2)","PFJet (QCD V9)","CaloJet (QCD V7.4.2)","CaloJet (QCD V9)" \
		--file QCD_V7p42.root,QCD_V9.root,QCD_V7p42.root,QCD_V9.root \
		--numerator "PuppiJet_EtaPT100_000000","PuppiJet_EtaPT100_000000","CaloJet_EtaPT100_000000","CaloJet_EtaPT100_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -3.2 --xmax 3.2 --output V9_004.pdf
	./Execute \
		--label "PFTau (HTauTau V8.2 GenVisTau)","PFTau (SingleTau V9 GenTau)","PFIsoTau (HTauTau V8.2 GenVisTau)","PFIsoTau (SingleTau V9 GenTau)" \
		--file HTauTau_V8p2.root,SingleTau_V9.root,HTauTau_V8p2.root,SingleTau_V9.root \
		--numerator "PFTauIso_PT_000000","PFTauIso_PT_000000","PFIsoTau_PT_000000","PFIsoTau_PT_000000" \
		--denominator "auto","auto","PFTauIsoNoMatch_PT_000000","PFTauIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9_005.pdf
	./Execute \
		--label "PFTau (HTauTau V8.2 GenVisTau)","PFTau (SingleTau V9 GenTau)","PFIsoTau (HTauTau V8.2 GenVisTau)","PFIsoTau (SingleTau V9 GenTau)" \
		--file HTauTau_V8p2.root,SingleTau_V9.root,HTauTau_V8p2.root,SingleTau_V9.root \
		--numerator "PFTauIso_EtaPT30_000000","PFTauIso_EtaPT30_000000","PFIsoTau_EtaPT30_000000","PFIsoTau_EtaPT30_000000" \
		--denominator "auto","auto","PFTauIsoNoMatch_EtaPT30_000000","PFTauIsoNoMatch_EtaPT30_000000" \
		--title ";#eta;Efficiency" --xmin -3.2 --xmax 3.2 --output V9_006.pdf
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "PuppiJet_PT_000000","PuppiJet_PT_000000","CaloJet_PT_000000","CaloJet_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output V9_007.pdf
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "PuppiJetWide_EtaPT100_000000","PuppiJetWide_EtaPT100_000000","CaloJetWide_EtaPT100_000000","CaloJetWide_EtaPT100_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -5.2 --xmax 5.2 --output V9_008.pdf
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "PuppiJet_PTEta15_000000","PuppiJet_PTEta15_000000","CaloJet_PTEta15_000000","CaloJet_PTEta15_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output V9_009.pdf
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "PuppiJet_PTEtaLarge_000000","PuppiJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000","CaloJet_PTEtaLarge_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output V9_010.pdf
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "PuppiJetForward_PT_000000","PuppiJetForward_PT_000000","CaloJetFoward_PT_000000","CaloJetFoward_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output V9_011.pdf
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V9)","TkElectron (DYLL V7.5.2)","TkElectron (DYLL V9)","TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000" \
		--denominator "auto","auto","auto","auto","TkElectronIsoNoMatch_PTEta15_000000","TkElectronIsoNoMatch_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9_012.pdf
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V9)","TkElectron (DYLL V7.5.2)","TkElectron (DYLL V9)","TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000" \
		--denominator "auto","auto","auto","auto","TkElectronIsoNoMatch_PTEtaLarge_000000","TkElectronIsoNoMatch_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9_014.pdf
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V9)","TkElectron (DYLL V7.5.2)","TkElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000","TkElectronTrackIDExtendedIso_PT_000000","TkElectronTrackIDExtendedIso_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V9_015.pdf
	./Execute \
		--label "EGElectron (DYLL V7.5.2)","EGElectron (DYLL V9)","TkElectron (DYLL V7.5.2)","TkElectron (DYLL V9)","TkIsoElectron (DYLL V7.5.2)","TkIsoElectron (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "EGTrackIDIso_EtaPT15_000000","EGTrackIDIso_EtaPT15_000000","TkElectronTrackIDIso_EtaPT15_000000","TkElectronTrackIDIso_EtaPT15_000000","TkIsoElectron_EtaPT15_000000","TkIsoElectron_EtaPT15_000000" \
		--denominator "auto","auto","auto","auto","TkElectronIsoNoMatch_EtaPT15_000000","TkElectronIsoNoMatch_EtaPT15_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output V9_016.pdf
	./Execute \
		--label "PFJet (DYLL V7.5.2)","PFJet (DYLL V9)","CaloJet (DYLL V7.5.2)","CaloJet (DYLL V9)" \
		--file DYLL_V7p52.root,DYLL_V9.root,DYLL_V7p52.root,DYLL_V9.root \
		--numerator "PuppiJetWide_EtaPT30_000000","PuppiJetWide_EtaPT30_000000","CaloJetWide_EtaPT30_000000","CaloJetWide_EtaPT30_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -5.2 --xmax 5.2 --output V9_017.pdf
	cp V9_*pdf ~/public/html/

V7V8Comparison: Execute
	./Execute \
		--label "Barrel (V7.4)","Endcap (V7.4)","Barrel (V8.2)","Endcap (V8.2)" \
		--file $(HGG),$(HGG),$(NewHGG),$(NewHGG) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000","TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative","cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0.0 --xmax 0.6 --ymin 0.5 --ymax 1.0 --line 0.946 --grid true \
		--output Photon.pdf
	./Execute \
		--label "Barrel (V7.5.2)","Endcap (V7.5.2)","Barrel (V8.2)","Endcap (V8.2)" \
		--file $(DYLL),$(DYLL),$(NewDYLL),$(NewDYLL) \
		--numerator "TkElectronTrackIDIso_TkIsoPT10Eta15_000000","TkElectronTrackIDIso_TkIsoPT10EtaLarge_000000","TkElectronTrackIDIso_TkIsoPT10Eta15_000000","TkElectronTrackIDIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative","cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0.0 --xmax 1.0 --ymin 0.88 --ymax 1.0 --line 0.982 --grid true \
		--output Electron.pdf

V8Comparison: Execute
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "EGIso_EtaPT20_000000","EGIso_EtaPT20_000000" \
		--denominator "auto","auto" \
		--title ";#eta;Efficiency" --xmin -3.0 --xmax 3.0 --output V8_001.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "EGIso_PTEta15_000000","EGIso_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_002.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "EGIso_PTEtaLarge_000000","EGIso_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_003.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "EGExtendedIso_EtaPT20_000000","EGExtendedIso_EtaPT20_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin -3.0 --xmax 3.0 --output V8_004.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "EGExtendedIso_PT_000000","EGExtendedIso_PT_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_005.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "EGTrackIDIso_EtaPT20_000000","EGTrackIDIso_EtaPT20_000000" \
		--denominator "auto","auto" \
		--title ";#eta;Efficiency" --xmin -3.0 --xmax 3.0 --output V8_006.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "EGTrackIDIso_PTEta15_000000","EGTrackIDIso_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_007.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "EGTrackIDIso_PTEtaLarge_000000","EGTrackIDIso_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_008.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "EGTrackIDExtendedIso_EtaPT20_000000","EGTrackIDExtendedIso_EtaPT20_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin -3.0 --xmax 3.0 --output V8_009.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "EGTrackIDExtendedIso_PT_000000","EGTrackIDExtendedIso_PT_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_010.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "TkElectronTrackIDIso_EtaPT20_000000","TkElectronTrackIDIso_EtaPT20_000000" \
		--denominator "auto","auto" \
		--title ";#eta;Efficiency" --xmin -3.0 --xmax 3.0 --output V8_011.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "TkElectronTrackIDIso_PTEta15_000000","TkElectronTrackIDIso_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_012.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "TkElectronTrackIDIso_PTEtaLarge_000000","TkElectronTrackIDIso_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_014.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "TkIsoPhotonTrackID_EtaPT20_000000","TkIsoPhotonTrackID_EtaPT20_000000" \
		--denominator "auto","auto" \
		--title ";#eta;Efficiency" --xmin -3.0 --xmax 3.0 --output V8_015.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonTrackID_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_016.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "TkIsoPhotonTrackID_PTEtaLarge_000000","TkIsoPhotonTrackID_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_017.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "TkIsoPhotonPVTrackID_EtaPT20_000000","TkIsoPhotonPVTrackID_EtaPT20_000000" \
		--denominator "auto","auto" \
		--title ";#eta;Efficiency" --xmin -3.0 --xmax 3.0 --output V8_018.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "TkIsoPhotonPVTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_019.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(HGG),$(NewHGG) \
		--numerator "TkIsoPhotonPVTrackID_PTEtaLarge_000000","TkIsoPhotonPVTrackID_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_020.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "TkIsoElectron_EtaPT20_000000","TkIsoElectron_EtaPT20_000000" \
		--denominator "auto","auto" \
		--title ";#eta;Efficiency" --xmin -3.0 --xmax 3.0 --output V8_021.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_022.pdf
	./Execute \
		--label "Madrid","V8" \
		--file $(DYLL),$(NewDYLL) \
		--numerator "TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_023.pdf
	./Execute \
		--label "PFTau","PFIsoTau","NNTau","NNTau (loose)","CaloTau","NNTau (No ID)" \
		--file $(NewHTauTau),$(NewHTauTau),$(NewHTauTau),$(NewHTauTau),$(NewHTauTau),$(NewHTauTau) \
		--numerator "PFTauIso_EtaPT30_000000","PFIsoTau_EtaPT30_000000","NNTauIso_EtaPT30_000000","NNTauLooseIso_EtaPT30_000000","CaloTauIso_EtaPT30_000000","NNTauNoIDIso_EtaPT30_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -3.0 --xmax 3.0 --output V8_024.pdf
	./Execute \
		--label "PFTau","PFIsoTau","NNTau","NNTau (loose)","CaloTau","NNTau (No ID)" \
		--file $(NewHTauTau),$(NewHTauTau),$(NewHTauTau),$(NewHTauTau),$(NewHTauTau),$(NewHTauTau) \
		--numerator "PFTauIso_PT_000000","PFIsoTau_PT_000000","NNTauIso_PT_000000","NNTauLooseIso_PT_000000","CaloTauIso_PT_000000","NNTauNoIDIso_PT_000000" \
		--denominator "auto","auto","auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output V8_025.pdf
	./Execute \
		--label "NNTau (ID = 1)","NNTau (ID = 2)","NNTau (ID = 3)","NNTau (ID = 4)","NNTau (ID = 5)" \
		--file $(NewHTauTau),$(NewHTauTau),$(NewHTauTau),$(NewHTauTau),$(NewHTauTau) \
		--numerator "NNTauIso1_EtaPT30_000000","NNTauIso2_EtaPT30_000000","NNTauIso3_EtaPT30_000000","NNTauIso4_EtaPT30_000000","NNTauIso5_EtaPT30_000000" \
		--denominator "auto","auto","auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -3.0 --xmax 3.0 --ymin 1e-5 --ymax 0.2 --output V8_026.pdf --logy true
	cp V8*pdf ~/public/html/

MariaPlotsTest: Execute
	./Execute \
		--label "Regular" \
		--file $(DYLL) \
		--numerator "StandaloneMuonIso_EtaPT15_000000" \
		--denominator "auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output STAMuon.pdf
	./Execute \
		--label "Displaced (*)" \
		--file $(DYLL) \
		--numerator "StandaloneDisplacedMuonIso_EtaPT15_000000" \
		--denominator "auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output STADisplaced.pdf
	cp *pdf ~/public/html/

MariaPlots: Execute
	./Execute \
		--label "Electron","Photon" \
		--file $(DYLL),$(HGG) \
		--numerator "EGTrackID_PTEta15_000000","EG_PTEta15_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output 001.pdf
	./Execute \
		--label "Electron","Photon" \
		--file $(DYLL),$(HGG) \
		--numerator "EGTrackID_PTEtaLarge_000000","EG_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output 002.pdf
	./Execute \
		--label "Electron","Photon" \
		--file $(DYLL),$(HGG) \
		--numerator "EGTrackID_EtaPT15_000000","EG_EtaPT15_000000" \
		--denominator "auto","auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output 003.pdf
	./Execute \
		--label "Barrel","Endcap" \
		--file $(DYLL),$(DYLL) \
		--numerator "TkElectronTrackID_PTEta15_000000","TkElectronTrackID_PTEtaLarge_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output 004.pdf
	./Execute \
		--label "Barrel","Endcap" \
		--file $(DYLL),$(DYLL) \
		--numerator "TkElectronTrackID_ResponsePT10Eta15_000000","TkElectronTrackID_ResponsePT10EtaLarge_000000" \
		--denominator "simple","simple" \
		--title ";L1 p_{T} / p_{T}^{Gen};a.u." --xmin 0.0 --xmax 2.5 --ymin 0.0 --ymax 10 --line "" \
		--output 005.pdf
	./Execute \
		--label "Barrel","Endcap" \
		--file $(DYLL),$(DYLL) \
		--numerator "TkElectronTrackID_ResponsePT10Eta15_000000","TkElectronTrackID_ResponsePT10EtaLarge_000000" \
		--denominator "simple","simple" \
		--title ";L1 p_{T} / p_{T}^{Gen};a.u." --xmin 0.0 --xmax 2.5 --ymin 0.0001 --ymax 25.0 --line "" \
		--legendx 0.55 --legendy 0.5 --logy true --output 005Log.pdf
	./Execute \
		--label "Barrel","Endcap" \
		--file $(DYLL),$(DYLL) \
		--numerator "TkElectronTrackID_PTEta15_003000","TkElectronTrackID_PTEtaLarge_003000" \
		--denominator "TkElectronTrackID_PTEta15_000000","TkElectronTrackID_PTEtaLarge_000000" \
		--title ";Gen p_{T};Efficiency" --xmin 0 --xmax 150 --output 006.pdf
	./Execute \
		--label "Barrel","Endcap" \
		--file $(DYLL),$(DYLL) \
		--numerator "TkElectronIso_TkIsoPT10Eta15_000000","TkElectronIso_TkIsoPT10EtaLarge_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0.0 --xmax 1.0 --ymin 0.9 --ymax 1.0 --line 0.982 --grid true \
		--output 007.pdf
	./Execute \
		--label "Barrel","Endcap" \
		--file $(DYLL),$(DYLL) \
		--numerator "TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEtaLarge_000000" \
		--denominator "TkElectronIsoNoMatch_PTEta15_000000","TkElectronIsoNoMatch_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output 008.pdf
	./Execute \
		--label "TkMatchedElectron","TkIsoMatchedElectron" \
		--file $(DYLL),$(DYLL) \
		--numerator "TkElectronTrackID_EtaPT20_000000","TkIsoElectron_EtaPT20_000000" \
		--denominator "auto","TkElectronIsoNoMatch_EtaPT20_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output 009.pdf
	./Execute \
		--label "TkIsoPhoton","TkIsoPhotonPV" \
		--file $(HGG),$(HGG) \
		--numerator "TkPhotonTrackIDIso_TkIsoPT10Eta15_000000","TkPhotonPVTrackIDIso_TkIsoPT10Eta15_000000" \
		--denominator "cumulative","cumulative" \
		--title ";Isolation;Efficiency" --xmin 0.0 --xmax 0.6 --ymin 0.9 --ymax 1.0 --line 0.946 --grid true \
		--legendx 0.45 --legendy 0.2 --output 010.pdf
	./Execute \
		--label "TkIsoPhoton","TkIsoPhotonPV" \
		--file $(HGG),$(HGG) \
		--numerator "TkIsoPhotonTrackID_PTEta15_000000","TkIsoPhotonPVTrackID_PTEta15_000000" \
		--denominator "TkPhotonTrackIDIsoNoMatch_PTEta15_000000","TkPhotonPVTrackIDIsoNoMatch_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output 011.pdf
	./Execute \
		--label "TkIsoPhoton","TkIsoPhotonPV" \
		--file $(HGG),$(HGG) \
		--numerator "TkIsoPhotonTrackID_EtaPT25_000000","TkIsoPhotonPVTrackID_EtaPT25_000000" \
		--denominator "TkPhotonTrackIDIsoNoMatch_EtaPT25_000000","TkPhotonPVTrackIDIsoNoMatch_EtaPT25_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output 012.pdf
	./Execute \
		--label "Threshold 100 GeV","Threshold 150 GeV" \
		--file $(QCD),$(QCD) \
		--numerator "CaloJet_PT_010000","CaloJet_PT_015000" \
		--denominator "CaloJet_PT_000000","CaloJet_PT_000000" \
		--title ";Gen p_{T};Efficiency" --xmin 0 --xmax 500 --output 013.pdf
	./Execute \
		--label "PFJet (ttbar)","CaloJet (ttbar)","CaloJet (QCD)" \
		--file $(TTbar),$(TTbar),$(QCD) \
		--numerator "PuppiJet_PT_000000","CaloJet_PT_000000","CaloJet_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output 014.pdf
	./Execute \
		--label "PFJet (ttbar)","PFJet (QCD)","CaloJet (ttbar)","CaloJet (QCD)" \
		--file $(TTbar),$(QCD),$(TTbar),$(QCD) \
		--numerator "PuppiJet_PT_000000","PuppiJet_PT_000000","CaloJet_PT_000000","CaloJet_PT_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output 014Crowded.pdf
	./Execute \
		--label "PFJet (ttbar)","CaloJet (ttbar)","CaloJet (QCD)" \
		--file $(TTbar),$(TTbar),$(QCD) \
		--numerator "PuppiJetWide_PT_000000","CaloJetWide_PT_000000","CaloJetWide_PT_000000" \
		--denominator "auto","auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output 014Wide.pdf
	./Execute \
		--label "CaloTkTau","TkEGTau" \
		--file $(HTauTau),$(HTauTau) \
		--numerator "CaloTkTau_PT_000000","TkEGTau_PT_000000" \
		--denominator "auto","auto" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output 015.pdf
	./Execute \
		--label "TkTau","CaloTkTau","TkEGTau" \
		--file $(HTauTau),$(HTauTau),$(HTauTau) \
		--numerator "TkTau_EtaPT30_000000","CaloTkTau_EtaPT30_000000","TkEGTau_EtaPT30_000000" \
		--denominator "auto","auto","auto" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output 016.pdf
	./Execute \
		--label "PFTau","PFIsoTau" \
		--file $(HTauTau),$(HTauTau) \
		--numerator "PFTau_PT_000000","PFIsoTau_PT_000000" \
		--denominator "auto","PFTauIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 150 --output 017.pdf
	./Execute \
		--label "PFTau","PFIsoTau" \
		--file $(HTauTau),$(HTauTau) \
		--numerator "PFTau_EtaPT30_000000","PFIsoTau_EtaPT30_000000" \
		--denominator "auto","PFTauIsoNoMatch_EtaPT30_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output 018.pdf
	cp *pdf ~/public/html

Plots21434: Execute
	./Execute \
		--label "Barrel 5 GeV","Barrel 9 GeV","Barrel 12 GeV","Barrel 15 GeV" \
		--file $(DYLL),$(DYLL),$(DYLL),$(DYLL) \
		--numerator "TkIsoElectron_PTEta15_000500","TkIsoElectron_PTEta15_000900","TkIsoElectron_PTEta15_001200","TkIsoElectron_PTEta15_001500" \
		--denominator "TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000","TkIsoElectron_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 50 --output 21434_001.pdf
	./Execute \
		--label "Endcap 5 GeV","Endcap 9 GeV","Endcap 12 GeV","Endcap 15 GeV" \
		--file $(DYLL),$(DYLL),$(DYLL),$(DYLL) \
		--numerator "TkIsoElectron_PTEtaLarge_000500","TkIsoElectron_PTEtaLarge_000900","TkIsoElectron_PTEtaLarge_001200","TkIsoElectron_PTEtaLarge_001500" \
		--denominator "TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000","TkIsoElectron_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 50 --output 21434_002.pdf
	./Execute \
		--label "50 GeV","70 GeV","80 GeV","100 GeV" \
		--file $(VBFHInv),$(VBFHInv),$(VBFHInv),$(VBFHInv) \
		--numerator "PuppiMET_PT_005000","PuppiMET_PT_007000","PuppiMET_PT_008000","PuppiMET_PT_010000" \
		--denominator "PuppiMET_PT_000000","PuppiMET_PT_000000","PuppiMET_PT_000000","PuppiMET_PT_000000" \
		--title ";MET;Efficiency" --xmin 0 --xmax 400 --output 21434_003.pdf
	cp 21434*pdf ~/public/html/

Execute: PlotComparison.cpp
	CompileRootMacro PlotComparison.cpp Execute
