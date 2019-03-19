default: RunGoodCalo 

TestRun: Execute
	time ./Execute --Input SmallTestInputFile.root \
		--Tree "ak4PFJetAnalyzer/t" --Output TestRun.root --PrintDebug false --RemoveHEM true --IsCalo false

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

Execute: QuickLook.cpp
	CompileRootMacro QuickLook.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*o

ExecutePlots: MakePlot.cpp
	CompileRootMacro MakePlot.cpp ExecutePlots \
		-I../../CommonCode/include ../../CommonCode/library/*o


