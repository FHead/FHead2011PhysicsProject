

default: TestRun

TestRun: Execute
	./Execute --Input Meow_5to22.root --Output DMass --Base HD1OppositeBase --Variant HD1OppositeVariant \
		--XMin 1.75 --XMax 2.00 --YMin 13.1 --YMax 18.9 --ExtraInfo "D^{0} p > 1 GeV/c"
	./Execute --Input Meow_5to22.root --Output DMassP2 --Base HD2OppositeBase --Variant HD2OppositeVariant \
		--XMin 1.75 --XMax 2.00 --YMin 10.1 --YMax 15.4 --ExtraInfo "D^{0} p > 2 GeV/c"

Execute: MakePlot.cpp
	g++ MakePlot.cpp -o Execute `root-config --cflags --glibs`
