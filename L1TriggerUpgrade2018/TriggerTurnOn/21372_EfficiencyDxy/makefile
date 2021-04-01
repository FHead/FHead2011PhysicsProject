DYLL    = DYLL_V7p52.root
HGG     = HGG_V7p4.root
HTauTau = HTauTau_V7p5.root
WLNu    = WLNu_V6.root
VBFHInv = VBFHInv_V7p42.root
TTbar   = TTbar_V7p42.root
QCD     = QCD_V7p42.root
Displaced = DisplacedMuon_V7p52.root

default: DxyPlots

DxyPlots: Execute
	./Execute \
		--label "|eta| < 0.83" \
		--file $(Displaced) \
		--numerator "StandaloneDisplacedMuonBarrelIso_DXYPT20_000000" \
		--denominator "auto" \
		--title ";Gen Dxy;Efficiency;" --xmin 0 --xmax 100 --rebin 4 --output Muons.pdf
	./Execute \
		--label "D_{xy} > 0","D_{xy} > 20","D_{xy} > 50","D_{xy} > 80" \
		--file $(Displaced),$(Displaced),$(Displaced),$(Displaced) \
		--numerator "StandaloneDisplacedMuonBarrelIso_Eta_000000","StandaloneDisplacedMuonBarrelIso_EtaDXY20_000000","StandaloneDisplacedMuonBarrelIso_EtaDXY50_000000","StandaloneDisplacedMuonBarrelIso_EtaDXY80_000000" \
		--denominator "auto","auto","auto","auto" \
		--title ";#eta;Efficiency;" --xmin -1.1 --xmax 1.1 --rebin 1 --output MuonsEta.pdf \
		--legendx 0.30 --legendy 0.20
	cp *pdf ~/public/html

Execute: PlotComparison.cpp
	CompileRootMacro PlotComparison.cpp Execute
