

default: TestRun

TestRun: Execute
	./Execute --Input Meow_5to22_20210416.root --Output DMassP1_20210416 \
		--Base HD1OppositeBase --Variant HD1OppositeVariant --Shift 3 \
		--XMin 1.75 --XMax 2.00 --YMin 13.1 --YMax 18.9 --ExtraInfo "D^{0} p > 1 GeV/c"
	./Execute --Input Meow_5to22_20210416.root --Output DMassP2_20210416 \
		--Base HD2OppositeBase --Variant HD2OppositeVariant --Shift 3 \
		--XMin 1.75 --XMax 2.00 --YMin 10.1 --YMax 15.4 --ExtraInfo "D^{0} p > 2 GeV/c"
	./Execute --Input Root_outputGan_20210417_092920_5to54.root --Output DMassP2_20210417 \
		--Base HD2OppositeBase --Variant HD2OppositeVariant --Shift 4 \
		--XMin 1.75 --XMax 2.00 --YMin 15.1 --YMax 20.2 --ExtraInfo "D^{0} p > 2 GeV/c"
	./Execute --Input Root_outputGan_20210417_092920_5to54.root --Output DMassP3_20210417 \
		--Base HD3OppositeBase --Variant HD3OppositeVariant --Shift 4 \
		--XMin 1.75 --XMax 2.00 --YMin 10.1 --YMax 15.2 --ExtraInfo "D^{0} p > 3 GeV/c"
	./Execute --Input Root_outputGanBin100_20210417_175143_5to54.root --Output DMassP2_20210417Bin100 \
		--Base HD2OppositeBase --Variant HD2OppositeVariant --Shift 4 \
		--XMin 1.75 --XMax 2.00 --YMin 15.1 --YMax 20.2 --ExtraInfo "D^{0} p > 2 GeV/c"
	./Execute --Input Root_outputGanBin100_20210417_175143_5to54.root --Output DMassP3_20210417Bin100 \
		--Base HD3OppositeBase --Variant HD3OppositeVariant --Shift 4 \
		--XMin 1.75 --XMax 2.00 --YMin 10.1 --YMax 15.2 --ExtraInfo "D^{0} p > 3 GeV/c"
	./Execute --Input Root_outputGanBin10_20210419_103600_5to54.root --Output DMassP2_20210419Bin10 \
		--Base HD2OppositeBase --Variant HD2OppositeVariant --Shift 4 \
		--XMin 1.75 --XMax 2.00 --YMin 15.1 --YMax 20.2 --ExtraInfo "D^{0} p > 2 GeV/c"
	./Execute --Input Root_outputGanBin10_20210419_103600_5to54.root --Output DMassP3_20210419Bin10 \
		--Base HD3OppositeBase --Variant HD3OppositeVariant --Shift 4 \
		--XMin 1.75 --XMax 2.00 --YMin 10.1 --YMax 15.2 --ExtraInfo "D^{0} p > 3 GeV/c"

Execute: MakePlot.cpp
	g++ MakePlot.cpp -o Execute `root-config --cflags --glibs`
