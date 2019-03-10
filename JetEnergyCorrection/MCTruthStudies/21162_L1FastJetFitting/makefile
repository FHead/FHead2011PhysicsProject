default: TestRun

TestRun: RunTree Execute
	# ./RunTree --input Trees/All_AK4PF.root --output Trees/Bin41_AK4PF.root \
	# 	--EtaMin 0.000 --EtaMax 0.078 --RecoDRCut 0.05 --PTHatMin 0 --PTHatMax 1000
	time ./Execute --input Trees/Bin41_AK4PF.root --tree FitData --output ResultMikko.pdf --function MikkoSuggestion
	time ./Execute --input Trees/Bin41_AK4PF.root --tree FitData --output ResultAndrew.pdf --function Andrew2017
	cp *.pdf ~/public/html/

RunTree: PrepareTree.cpp
	CompileRootMacro PrepareTree.cpp RunTree

Execute: PerformFit.cpp
	CompileRootMacro PerformFit.cpp Execute

