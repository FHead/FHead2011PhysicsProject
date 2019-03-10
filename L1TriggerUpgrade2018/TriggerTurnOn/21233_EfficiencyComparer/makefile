default: STAMuon GlobalMuon TkMuon MuonStub TkElectron TkIsoElectron

MuonStub: Execute
	./Execute \
		--label "TkMuon","TkMuonStub" \
		--file "DYLL_V7.root","DYLL_V7.root" \
		--numerator "TkMuonBarrelIso/TkMuonBarrelIso_PT_000000","TkMuonStubBarrelIso/TkMuonStubBarrelIso_PT_000000" \
		--denominator "TkMuonBarrelIso/TkMuonBarrelIsoNoMatch_PT_000000","TkMuonStubBarrelIso/TkMuonStubBarrelIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 75 --output MuonStub.pdf
	./Execute \
		--label "TkMuon","TkMuonStub" \
		--file "DYLL_V7.root","DYLL_V7.root" \
		--numerator "TkMuonIso/TkMuonIso_Eta_000000","TkMuonStubIso/TkMuonStubIso_Eta_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_Eta_000000","TkMuonStubIso/TkMuonStubIsoNoMatch_Eta_000000" \
		--title ";p_{T};Efficiency" --xmin -1.2 --xmax 1.2 --output MuonStubEtaNoPTCut.pdf
	./Execute \
		--label "TkMuon","TkMuonStub" \
		--file "DYLL_V7.root","DYLL_V7.root" \
		--numerator "TkMuonIso/TkMuonIso_EtaPT15_000000","TkMuonStubIso/TkMuonStubIso_EtaPT15_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_EtaPT15_000000","TkMuonStubIso/TkMuonStubIsoNoMatch_EtaPT15_000000" \
		--title ";p_{T};Efficiency" --xmin -1.2 --xmax 1.2 --output MuonStubEtaPT15.pdf
	cp MuonStub*.pdf ~/public/html/

STAMuon: Execute
	./Execute \
		--label "MuonKF (V6.3)","StandaloneMuon (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root"\
		--numerator "MuonKFIso/MuonKFIso_PT_000000","StandaloneMuonIso/StandaloneMuonIso_PT_000000" \
		--denominator "MuonKFIso/MuonKFIsoNoMatch_PT_000000","StandaloneMuonIso/StandaloneMuonIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 75 --output STAMuonPT.pdf
	./Execute \
		--label "MuonKF (V6.3)","StandaloneMuon (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root" \
		--numerator "MuonKFIso/MuonKFIso_EtaPT15_000000","StandaloneMuonIso/StandaloneMuonIso_EtaPT15_000000" \
		--denominator "MuonKFIso/MuonKFIsoNoMatch_EtaPT15_000000","StandaloneMuonIso/StandaloneMuonIsoNoMatch_EtaPT15_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output STAMuonEta.pdf
	cp STAMuon*.pdf ~/public/html/

GlobalMuon: Execute
	./Execute \
		--label "Muon (V6.3)","GlobalMuon (V7)","StandAloneMuon (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root","DYLL_V7.root" \
		--numerator "MuonIso/MuonIso_PT_000000","GlobalMuonIso/GlobalMuonIso_PT_000000","StandaloneMuonIso/StandaloneMuonIso_PT_000000" \
		--denominator "MuonIso/MuonIsoNoMatch_PT_000000","GlobalMuonIso/GlobalMuonIsoNoMatch_PT_000000","StandaloneMuonIso/StandaloneMuonIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 75 --output GlobalMuonPT.pdf
	./Execute \
		--label "Muon (V6.3)","GlobalMuon (V7)","StandaloneMuon (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root","DYLL_V7.root"  \
		--numerator "MuonIso/MuonIso_EtaPT15_000000","GlobalMuonIso/GlobalMuonIso_EtaPT15_000000","StandaloneMuonIso/StandaloneMuonIso_EtaPT15_000000" \
		--denominator "MuonIso/MuonIsoNoMatch_EtaPT15_000000","GlobalMuonIso/GlobalMuonIsoNoMatch_EtaPT15_000000","StandaloneMuonIso/StandaloneMuonIsoNoMatch_EtaPT15_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output GlobalMuonEta.pdf
	cp GlobalMuon*.pdf ~/public/html/

TkMuon: Execute
	./Execute \
		--label "TkMuon (V6.3)","TkMuon (V7)","TkMuon no cut (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root","DYLL_V7.root" \
		--numerator "TkMuonIso/TkMuonIso_PT_000000","TkMuonIso/TkMuonIso_PT_000000","TkMuonNoCutIso/TkMuonNoCutIso_PT_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_PT_000000","TkMuonIso/TkMuonIsoNoMatch_PT_000000","TkMuonNoCutIso/TkMuonNoCutIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 75 --output TkMuonPT.pdf
	./Execute \
		--label "TkMuon (V6.3)","TkMuon (V7)","TkMuon no cut (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root","DYLL_V7.root" \
		--numerator "TkMuonIso/TkMuonIso_EtaPT15_000000","TkMuonIso/TkMuonIso_EtaPT15_000000","TkMuonNoCutIso/TkMuonNoCutIso_EtaPT15_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_EtaPT15_000000","TkMuonIso/TkMuonIsoNoMatch_EtaPT15_000000","TkMuonNoCutIso/TkMuonNoCutIsoNoMatch_EtaPT15_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output TkMuonEta.pdf
	cp TkMuon*.pdf ~/public/html/

TkElectron: Execute
	./Execute \
		--label "TkEG (V6.3)","TkElectron (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root" \
		--numerator "TkEGIso/TkEGIso_PT_000000","TkElectronIso/TkElectronIso_PT_000000" \
		--denominator "TkEGIso/TkEGIsoNoMatch_PT_000000","TkElectronIso/TkElectronIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 100 --output TkElectronPT.pdf
	./Execute \
		--label "TkEG (V6.3)","TkElectron (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root" \
		--numerator "TkEGIso/TkEGIso_EtaPT15_000000","TkElectronIso/TkElectronIso_EtaPT15_000000" \
		--denominator "TkEGIso/TkEGIsoNoMatch_EtaPT15_000000","TkElectronIso/TkElectronIsoNoMatch_EtaPT15_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output TkElectronEta.pdf
	./Execute \
		--label "TkEG (V6.3)","TkElectron (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root" \
		--numerator "TkEGIso/TkEGIso_PTEta15_000000","TkElectronIso/TkElectronIso_PTEta15_000000" \
		--denominator "TkEGIso/TkEGIsoNoMatch_PTEta15_000000","TkElectronIso/TkElectronIsoNoMatch_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 100 --output TkElectronBBPT.pdf
	./Execute \
		--label "TkEG (V6.3)","TkElectron (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root" \
		--numerator "TkEGIso/TkEGIso_PTEtaLarge_000000","TkElectronIso/TkElectronIso_PTEtaLarge_000000" \
		--denominator "TkEGIso/TkEGIsoNoMatch_PTEtaLarge_000000","TkElectronIso/TkElectronIsoNoMatch_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 100 --output TkElectronECPT.pdf
	cp TkElectron*.pdf ~/public/html/

TkIsoElectron: Execute
	./Execute \
		--label "TkIsoEG (V6.3)","TkIsoElectron (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root" \
		--numerator "TkIsoEGIso/TkIsoEGIso_PT_000000","TkIsoElectron/TkIsoElectron_PT_000000" \
		--denominator "TkEGIso/TkEGIsoNoMatch_PT_000000","TkElectronIso/TkElectronIsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 100 --output TkIsoElectronPT.pdf
	./Execute \
		--label "TkIsoEG (V6.3)","TkIsoElectron (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root" \
		--numerator "TkIsoEGIso/TkIsoEGIso_EtaPT15_000000","TkIsoElectron/TkIsoElectron_EtaPT15_000000" \
		--denominator "TkEGIso/TkEGIsoNoMatch_EtaPT15_000000","TkElectronIso/TkElectronIsoNoMatch_EtaPT15_000000" \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output TkIsoElectronEta.pdf
	./Execute \
		--label "TkIsoEG (V6.3)","TkIsoElectron (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root" \
		--numerator "TkIsoEGIso/TkIsoEGIso_PTEta15_000000","TkIsoElectron/TkIsoElectron_PTEta15_000000" \
		--denominator "TkEGIso/TkEGIsoNoMatch_PTEta15_000000","TkElectronIso/TkElectronIsoNoMatch_PTEta15_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 100 --output TkIsoElectronBBPT.pdf
	./Execute \
		--label "TkIsoEG (V6.3)","TkIsoElectron (V7)" \
		--file "WLNu_V6.root","DYLL_V7.root" \
		--numerator "TkIsoEGIso/TkIsoEGIso_PTEtaLarge_000000","TkIsoElectron/TkIsoElectron_PTEtaLarge_000000" \
		--denominator "TkEGIso/TkEGIsoNoMatch_PTEtaLarge_000000","TkElectronIso/TkElectronIsoNoMatch_PTEtaLarge_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 100 --output TkIsoElectronECPT.pdf
	cp TkIsoElectron*.pdf ~/public/html/

Execute: PlotComparison.cpp
	CompileRootMacro PlotComparison.cpp Execute
