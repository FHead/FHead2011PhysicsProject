default: CaloJet MuonStub TkIsoElectronPV

CaloJet: Execute
	./Execute \
		--label "TTbar","DYLL","QCD" \
		--file "TTbar_V7p4.root","DYLL_V7p4.root","QCD_V7p42.root" \
		--numerator "CaloJetWide/CaloJetWide_EtaPT100_000000","CaloJetWide/CaloJetWide_EtaPT100_000000","CaloJetWide/CaloJetWide_EtaPT100_000000" \
		--denominator "CaloJetWide/CaloJetWideNoMatch_EtaPT100_000000","CaloJetWide/CaloJetWideNoMatch_EtaPT100_000000","CaloJetWide/CaloJetWideNoMatch_EtaPT100_000000" \
		--title ";#eta;Efficiency" --xmin -5.2 --xmax 5.2 --output CaloJetEtaPT100.pdf
	./Execute \
		--label "TTbar","DYLL","QCD" \
		--file "TTbar_V7p4.root","DYLL_V7p4.root","QCD_V7p42.root" \
		--numerator "CaloJetBarrel/CaloJetBarrel_PT_000000","CaloJetBarrel/CaloJetBarrel_PT_000000","CaloJetBarrel/CaloJetBarrel_PT_000000" \
		--denominator "CaloJetBarrel/CaloJetBarrelNoMatch_PT_000000","CaloJetBarrel/CaloJetBarrelNoMatch_PT_000000","CaloJetBarrel/CaloJetBarrelNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output CaloJetPTBarrel.pdf
	./Execute \
		--label "TTbar","DYLL","QCD" \
		--file "TTbar_V7p4.root","DYLL_V7p4.root","QCD_V7p42.root" \
		--numerator "CaloJetEndcap/CaloJetEndcap_PT_000000","CaloJetEndcap/CaloJetEndcap_PT_000000","CaloJetEndcap/CaloJetEndcap_PT_000000" \
		--denominator "CaloJetEndcap/CaloJetEndcapNoMatch_PT_000000","CaloJetEndcap/CaloJetEndcapNoMatch_PT_000000","CaloJetEndcap/CaloJetEndcapNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 500 --output CaloJetPTEndcap.pdf
	cp CaloJet*pdf ~/public/html

MuonStub: Execute
	./Execute \
		--label "TkMuon","TkMuonStub" \
		--file "DYLL_V7p4.root","DYLL_V7p4.root" \
		--numerator "TkMuonBarrelIso/TkMuonBarrelIso_PT_000000","TkMuonStubBarrelIso/TkMuonStubBarrelIso_PT_000000" \
		--denominator "TkMuonBarrelIso/TkMuonBarrelIsoNoMatch_PT_000000","TkMuonStubBarrelIso/TkMuonStubBarrelIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 75 --output MuonStub.pdf
	./Execute \
		--label "TkMuon","TkMuonStub" \
		--file "DYLL_V7p4.root","DYLL_V7p4.root" \
		--numerator "TkMuonIso/TkMuonIso_Eta_000000","TkMuonStubIso/TkMuonStubIso_Eta_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_Eta_000000","TkMuonStubIso/TkMuonStubIsoNoMatch_Eta_000000" \
		--title ";p_{T};Efficiency" --xmin -2.5 --xmax 2.5 --output MuonStubEtaNoPTCut.pdf
	./Execute \
		--label "TkMuon","TkMuonStub","TkMuonStub (V7.3)" \
		--file "DYLL_V7p4.root","DYLL_V7p4.root","DYLL_V7p3.root" \
		--numerator "TkMuonIso/TkMuonIso_EtaPT15_000000","TkMuonStubIso/TkMuonStubIso_EtaPT15_000000","TkMuonStubIso/TkMuonStubIso_EtaPT15_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_EtaPT15_000000","TkMuonStubIso/TkMuonStubIsoNoMatch_EtaPT15_000000","TkMuonStubIso/TkMuonStubIsoNoMatch_EtaPT15_000000" \
		--title ";p_{T};Efficiency" --xmin -2.5 --xmax 2.5 --output MuonStubEtaPT15.pdf
	./Execute \
		--label "TkMuon","TkMuonStub" \
		--file "DYLL_V7p4.root","DYLL_V7p4.root" \
		--numerator "TkMuonIso/TkMuonIso_EtaPT3to15_000000","TkMuonStubIso/TkMuonStubIso_EtaPT3to15_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_EtaPT3to15_000000","TkMuonStubIso/TkMuonStubIsoNoMatch_EtaPT3to15_000000" \
		--title ";p_{T};Efficiency" --xmin -2.5 --xmax 2.5 --output MuonStubEtaPT3to15.pdf
	cp MuonStub*.pdf ~/public/html/

TkIsoElectronPV: Execute
	./Execute \
		--label "TkIsoElectron (Electron)","TkIsoPhotonPV (Electron)","TkIsoElectronPV (Electron)" \
		--file "DYLL_V7p4.root","DYLL_V7p4.root","DYLL_V7p4.root" \
		--numerator "TkIsoElectron/TkIsoElectron_PT_000000","TkIsoPhotonPVEleTrackID/TkIsoPhotonPVEleTrackID_PT_000000","TkIsoElectronPV/TkIsoElectronPV_PT_000000" \
		--denominator "TkElectronIso/TkElectronIsoNoMatch_PT_000000","TkPhotonPVEleTrackIDIso/TkPhotonPVEleTrackIDIsoNoMatch_PT_000000","TkElectronPVIso/TkElectronPVIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 100 --output TkIsoElectronPVPT.pdf
	./Execute \
		--label "TkIsoElectron (Electron)","TkIsoPhotonPV (Electron)","TkIsoElectronPV (Electron)" \
		--file "DYLL_V7p4.root","DYLL_V7p4.root","DYLL_V7p4.root" \
		--numerator "TkIsoElectron/TkIsoElectron_PTEta15_000000","TkIsoPhotonPVEleTrackID/TkIsoPhotonPVEleTrackID_PTEta15_000000","TkIsoElectronPV/TkIsoElectronPV_PTEta15_000000" \
		--denominator "TkElectronIso/TkElectronIsoNoMatch_PTEta15_000000","TkPhotonPVEleTrackIDIso/TkPhotonPVEleTrackIDIsoNoMatch_PTEta15_000000","TkElectronPVIso/TkElectronPVIsoNoMatch_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 100 --output TkIsoElectronPVPTEta15.pdf
	./Execute \
		--label "TkIsoElectron (Electron)","TkIsoPhotonPV (Electron)","TkIsoElectronPV (Electron)" \
		--file "DYLL_V7p4.root","DYLL_V7p4.root","DYLL_V7p4.root" \
		--numerator "TkIsoElectron/TkIsoElectron_PTEtaLarge_000000","TkIsoPhotonPVEleTrackID/TkIsoPhotonPVEleTrackID_PTEtaLarge_000000","TkIsoElectronPV/TkIsoElectronPV_PTEtaLarge_000000" \
		--denominator "TkElectronIso/TkElectronIsoNoMatch_PTEtaLarge_000000","TkPhotonPVEleTrackIDIso/TkPhotonPVEleTrackIDIsoNoMatch_PTEtaLarge_000000","TkElectronPVIso/TkElectronPVIsoNoMatch_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 100 --output TkIsoElectronPVPTEtaLarge.pdf
	./Execute \
		--label "TkIsoElectron (Electron)","TkIsoPhotonPV (Electron)","TkIsoElectronPV (Electron)" \
		--file "DYLL_V7p4.root","DYLL_V7p4.root","DYLL_V7p4.root" \
		--numerator "TkIsoElectron/TkIsoElectron_EtaPT15_000000","TkIsoPhotonPVEleTrackID/TkIsoPhotonPVEleTrackID_EtaPT15_000000","TkIsoElectronPV/TkIsoElectronPV_EtaPT15_000000" \
		--denominator "TkElectronIso/TkElectronIsoNoMatch_EtaPT15_000000","TkPhotonPVEleTrackIDIso/TkPhotonPVEleTrackIDIsoNoMatch_EtaPT15_000000","TkElectronPVIso/TkElectronPVIsoNoMatch_EtaPT15_000000" \
		--title ";p_{T};Efficiency" --xmin -2.5 --xmax 2.5 --output TkIsoElectronPVEtaPT15.pdf
	cp TkIsoElectronPV*.pdf ~/public/html/

Execute: PlotComparison.cpp
	CompileRootMacro PlotComparison.cpp Execute
