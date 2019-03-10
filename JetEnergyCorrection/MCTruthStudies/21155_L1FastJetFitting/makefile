# InputFile = Output/Parameter_ak4pf.root
InputFile = 21153/Parameter_NoPTHatCut_ak4pfchs.root
Bin       = 45

default: TestRun

TestRun: FitMikkoSuggestionExtraFull FitMikkoSuggestionFull FitMikkoSuggestion FitAndrew2017

FitMikkoSuggestionExtraFull: Execute
	./Execute --input $(InputFile) \
		--graph p_offOverA_EtaVsRhoVsJetPt/p_offOverA_RhoVsJetPt_$(Bin) \
		--output Fit_EtaBin$(Bin)_MikkoSuggestionExtraFull.pdf \
		--function MikkoSuggestionExtraFull
	cp *pdf ~/public/html/

FitMikkoSuggestionFull: Execute
	./Execute --input $(InputFile) \
		--graph p_offOverA_EtaVsRhoVsJetPt/p_offOverA_RhoVsJetPt_$(Bin) \
		--output Fit_EtaBin$(Bin)_MikkoSuggestionFull.pdf \
		--function MikkoSuggestionFull
	cp *pdf ~/public/html/

FitMikkoSuggestion: Execute
	./Execute --input $(InputFile) \
		--graph p_offOverA_EtaVsRhoVsJetPt/p_offOverA_RhoVsJetPt_$(Bin) \
		--output Fit_EtaBin$(Bin)_MikkoSuggestion.pdf \
		--function MikkoSuggestion
	cp *pdf ~/public/html/

FitAndrew2017: Execute
	./Execute --input $(InputFile) \
		--graph p_offOverA_EtaVsRhoVsJetPt/p_offOverA_RhoVsJetPt_$(Bin) \
		--output Fit_EtaBin$(Bin)_Andrew2017.pdf \
		--function Andrew2017
	cp *pdf ~/public/html/

PlotAndrew2017Preset: Execute
	./Execute --input $(InputFile) \
		--graph p_offOverA_EtaVsRhoVsJetPt/p_offOverA_RhoVsJetPt_$(Bin) \
		--output Fit_EtaBin$(Bin)_Andrew2017Preset.pdf \
		--function Andrew2017Preset
	cp *pdf ~/public/html/

Execute: FitOffset.cpp
	CompileRootMacro FitOffset.cpp Execute


