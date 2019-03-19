default: RunGoodCalo 

TestRun: Execute
	time ./Execute --Input SmallTestInputFileGood.root \
		--Tree "ak4CaloJetAnalyzer/t" --Output TestRunGood.root --PrintDebug false --RemoveHEM true --IsCalo true
	./ExecutePlots --Input TestRunGood.root --Output TestRunGood.pdf
	time ./Execute --Input SmallTestInputFileBad.root \
		--Tree "ak4CaloJetAnalyzer/t" --Output TestRunBad.root --PrintDebug false --RemoveHEM true --IsCalo true
	./ExecutePlots --Input TestRunBad.root --Output TestRunBad.pdf

RunGoodCalo: Execute ExecutePlots
	time ./Execute --Input `ls SampleGoodEE/*root | tr '\n' ','` \
		--Tree "ak4CaloJetAnalyzer/t" --Output ResultGoodEECalo.root --PrintDebug false --RemoveHEM true --IsCalo true
	./ExecutePlots --Input ResultGoodEECalo.root --Output ResultGoodEECalo.pdf
	cp ResultGoodEECalo.pdf ~/public/html

RunGoodPF: Execute ExecutePlots
	time ./Execute --Input `ls SampleGoodEE/*root | tr '\n' ','` \
		--Tree "ak4PFJetAnalyzer/t" --Output ResultGoodEEPF.root --PrintDebug false --RemoveHEM true --IsCalo false
	./ExecutePlots --Input ResultGoodEEPF.root --Output ResultGoodEEPF.pdf
	cp ResultGoodEEPF.pdf ~/public/html

RunBadCaloPartial: Execute ExecutePlots
	time ./Execute --Input `ls SampleBadEE/*root | head -n 10 | tr '\n' ','` \
		--Tree "ak4CaloJetAnalyzer/t" --Output ResultBadEECalo.root --PrintDebug false --RemoveHEM true --IsCalo true
	./ExecutePlots --Input ResultBadEECalo.root --Output ResultBadEECalo.pdf
	cp ResultBadEECalo.pdf ~/public/html

RunBadCalo: Execute ExecutePlots
	time ./Execute --Input `ls SampleBadEE/*root | tr '\n' ','` \
		--Tree "ak4CaloJetAnalyzer/t" --Output ResultBadEECalo.root --PrintDebug false --RemoveHEM true --IsCalo true
	./ExecutePlots --Input ResultBadEECalo.root --Output ResultBadEECalo.pdf
	cp ResultBadEECalo.pdf ~/public/html

RunBadPFPartial: Execute ExecutePlots
	time ./Execute --Input `ls SampleBadEE/*root | head -n 10 | tr '\n' ','` \
		--Tree "ak4PFJetAnalyzer/t" --Output ResultBadEEPF.root --PrintDebug false --RemoveHEM true --IsCalo false
	./ExecutePlots --Input ResultBadEEPF.root --Output ResultBadEEPF.pdf
	cp ResultBadEEPF.pdf ~/public/html

RunBadPF: Execute ExecutePlots
	time ./Execute --Input `ls SampleBadEE/*root | tr '\n' ','` \
		--Tree "ak4PFJetAnalyzer/t" --Output ResultBadEEPF.root --PrintDebug false --RemoveHEM true --IsCalo false
	./ExecutePlots --Input ResultBadEEPF.root --Output ResultBadEEPF.pdf
	cp ResultBadEEPF.pdf ~/public/html

RunAnalysis: ExecuteAnalysis
	./ExecuteAnalysis --Input ResultBadEEPF.root --OutputBase AnalyzeBadEEPF
	./ExecuteAnalysis --Input TestRun.root --OutputBase AnalyzeGoodEEPF
	cp AnalyzeBadEEPF.pdf ~/public/html/
	cp AnalyzeGoodEEPF.pdf ~/public/html/

Execute: QuickLook.cpp
	CompileRootMacro QuickLook.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*o

ExecutePlots: MakePlot.cpp
	CompileRootMacro MakePlot.cpp ExecutePlots \
		-I../../CommonCode/include ../../CommonCode/library/*o

ExecuteAnalysis: Analyze.cpp
	CompileRootMacro Analyze.cpp ExecuteAnalysis

