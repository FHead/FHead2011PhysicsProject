default: TestRun

Execute: MakePlots.cpp
	CompileRootMacro MakePlots.cpp Execute

TestRun: Execute
	time ./Execute -input Result/Merged_MCV8.root -output ClosurePlotsTestRun.pdf -fraction 0.05
	cp ClosurePlotsTestRun.pdf ClosurePlots.pdf

FullRun: Execute
	time ./Execute -input Result/Merged_MCV8.root -output ClosurePlotsFullRun.pdf
	cp ClosurePlotsFullRun.pdf ClosurePlots.pdf

TestRunAndrew20180523: Execute
	time ./Execute -input Result/Merged_Andrew20180523.root -output ClosurePlotsTestRunAndrew20180523.pdf -fraction 0.05

FullRunAndrew20180523: Execute
	time ./Execute -input Result/Merged_Andrew20180523.root -output ClosurePlotsFullRunAndrew20180523.pdf

FullRunAndrew20180523BigRho: Execute
	time ./Execute -input Result/Merged_Andrew20180523_BigRho.root -output ClosurePlotsFullRunAndrew20180523BigRho.pdf

FullRunMagda: Execute
	time ./Execute -input Result/Merged_PuppiFlatDeriveL1.root -output PuppiFlatDeriveL1.pdf
	time ./Execute -input Result/Merged_PuppiFlatStandard.root -output PuppiFlatStandard.pdf
	time ./Execute -input Result/Merged_PuppiPremixL2L3Only.root -output PuppiPremixL2L3Only.pdf
	time ./Execute -input Result/Merged_PuppiPremixStandard.root -output PuppiPremixStandard.pdf
	time ./Execute -input Result/Merged_PuppiFlatL2L3Only.root -output PuppiFlatL2L3Only.pdf
	time ./Execute -input Result/Merged_PuppiPremixDeriveL1.root -output PuppiPremixDeriveL1.pdf
	time ./Execute -input Result/Merged_PuppiPremixPuppi.root -output PuppiPremixPuppi.pdf

FullRunSifuDebug17374: Execute
	time ./Execute -input Result/Merged_SifuDebug17374MarMar.root -output SifuDebug17374MarMar.pdf
	time ./Execute -input Result/Merged_SifuDebug17374MarMay.root -output SifuDebug17374MarMay.pdf
	time ./Execute -input Result/Merged_SifuDebug17374MayMar.root -output SifuDebug17374MayMar.pdf
	time ./Execute -input Result/Merged_SifuDebug17374MayMay.root -output SifuDebug17374MayMay.pdf



