default: MuonStub

MuonStub: Execute
	./Execute \
		--label "TkMuon","TkMuonStubS12" \
		--file "DYLL_V7p52.root","DYLL_V7p52.root" \
		--numerator "TkMuonBarrelIso/TkMuonBarrelIso_PT_000000","TkMuonStubS12BarrelIso/TkMuonStubS12BarrelIso_PT_000000" \
		--denominator "TkMuonBarrelIso/TkMuonBarrelIsoNoMatch_PT_000000","TkMuonStubS12BarrelIso/TkMuonStubS12BarrelIsoNoMatch_PT_000000" \
		--title "|#eta| < 0.83;p_{T};Efficiency" --xmin 0 --xmax 75 --output MuonComparisonPTBarrel.pdf
	./Execute \
		--label "TkMuon","TkMuonStubS12" \
		--file "DYLL_V7p52.root","DYLL_V7p52.root" \
		--numerator "TkMuonIso/TkMuonIso_PT_000000","TkMuonStubS12Iso/TkMuonStubS12Iso_PT_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_PT_000000","TkMuonStubS12Iso/TkMuonStubS12IsoNoMatch_PT_000000" \
		--title ";p_{T};Efficiency" --xmin 0 --xmax 75 --output MuonComparisonPTFullRange.pdf
	./Execute \
		--label "TkMuon","TkMuonStubS12" \
		--file "DYLL_V7p52.root","DYLL_V7p52.root" \
		--numerator "TkMuonIso/TkMuonIso_EtaPT3to15_000000","TkMuonStubS12Iso/TkMuonStubS12Iso_EtaPT3to15_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_EtaPT3to15_000000","TkMuonStubS12Iso/TkMuonStubS12IsoNoMatch_EtaPT3to15_000000" \
		--color 632,417 \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output MuonComparisonPT3to15.pdf
	./Execute \
		--label "TkMuon","TkMuonStubS12" \
		--file "DYLL_V7p52.root","DYLL_V7p52.root" \
		--numerator "TkMuonIso/TkMuonIso_EtaPT3to5_000000","TkMuonStubS12Iso/TkMuonStubS12Iso_EtaPT3to5_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_EtaPT3to5_000000","TkMuonStubS12Iso/TkMuonStubS12IsoNoMatch_EtaPT3to5_000000" \
		--color 632,417 \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output MuonComparisonPT3to5.pdf
	./Execute \
		--label "TkMuon","TkMuonStubS12" \
		--file "DYLL_V7p52.root","DYLL_V7p52.root" \
		--numerator "TkMuonIso/TkMuonIso_EtaPT3to6_000000","TkMuonStubS12Iso/TkMuonStubS12Iso_EtaPT3to6_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_EtaPT3to6_000000","TkMuonStubS12Iso/TkMuonStubS12IsoNoMatch_EtaPT3to6_000000" \
		--color 632,417 \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output MuonComparisonPT3to6.pdf
	./Execute \
		--label "TkMuon","TkMuonStubS12" \
		--file "DYLL_V7p52.root","DYLL_V7p52.root" \
		--numerator "TkMuonIso/TkMuonIso_EtaPT3to10_000000","TkMuonStubS12Iso/TkMuonStubS12Iso_EtaPT3to10_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_EtaPT3to10_000000","TkMuonStubS12Iso/TkMuonStubS12IsoNoMatch_EtaPT3to10_000000" \
		--color 632,417 \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output MuonComparisonPT3to10.pdf
	./Execute \
		--label "TkMuon","TkMuonStubS12" \
		--file "DYLL_V7p52.root","DYLL_V7p52.root" \
		--numerator "TkMuonIso/TkMuonIso_EtaPT15_000000","TkMuonStubS12Iso/TkMuonStubS12Iso_EtaPT15_000000" \
		--denominator "TkMuonIso/TkMuonIsoNoMatch_EtaPT15_000000","TkMuonStubS12Iso/TkMuonStubS12IsoNoMatch_EtaPT15_000000" \
		--color 632,417 \
		--title ";#eta;Efficiency" --xmin -2.5 --xmax 2.5 --output MuonComparisonPT15.pdf
	cp Muon*.pdf ~/public/html/

Execute: PlotComparison.cpp
	CompileRootMacro PlotComparison.cpp Execute
