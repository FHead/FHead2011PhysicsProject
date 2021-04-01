DYLL    = DYLL_V7p52.root
HGG     = HGG_V7p4.root
NewDYLL = DYLL_V8.root
NewHGG  = HGG_V8.root
HTauTau = HTauTau_V7p5.root
WLNu    = WLNu_V6.root
VBFHInv = VBFHInv_V7p42.root
TTbar   = TTbar_V7p42.root
QCD     = QCD_V7p42.root

default: V8Comparison

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
