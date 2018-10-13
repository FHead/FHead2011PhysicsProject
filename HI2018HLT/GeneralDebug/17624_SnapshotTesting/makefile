Dataset = /Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018/HINPbPbSpring18DR-NoPU_100X_upgrade2018_realistic_v10_ext1-v1/GEN-SIM-RAW

GetFileList:
	dasgoclient --query="file dataset=$(Dataset)" | sed "s/^/'/" | sed "s/$$/',/"> FileList

SubmitJob: GetFileList
	mkdir -p Result/
	bash Submit.sh

ResubmitJob:
	bash SubmitAgain.sh

Merge:
	hadd -f openHLT.root `ls -l Result/*root | awk '{if($$5 > 20000) print $$9}'`

ListBad:
	ls -l Result/*root | awk '{if($$5 < 20000) print $$9}' | cat -n

ListGood:
	ls -l Result/*root | awk '{if($$5 > 20000) print $$9}' | cat -n

CollectRates:
	bzgrep HLT-Report Result/Log_* | bzip2 > HLTRatesAll.txt.bz2

PrintRates:
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet40Eta5p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet50Eta5p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet60Eta5p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet70Eta5p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet80Eta5p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet90Eta5p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet100Eta5p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet110Eta5p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet120Eta5p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet40Fwd_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet50Fwd_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet60Fwd_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet70Fwd_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet80Fwd_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet90Fwd_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet100Fwd_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet110Fwd_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet120Fwd_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet80Eta2p4_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet90Eta2p4_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet100Eta2p4_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet110Eta2p4_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet120Eta2p4_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet60Eta1p5_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet70Eta1p5_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet80Eta1p5_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet90Eta1p5_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet100Eta1p5_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet110Eta1p5_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_CsAK4PFJet120Eta1p5_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet80_35_Eta1p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet100_35_Eta1p1_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet80_35_Eta0p7_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet100_35_Eta0p7_v1
	./PrintOnePath.sh HLTRatesAll.txt.bz2 HLT_PuAK4CaloJet80_45_45_Eta2p1_v1

CollectTiming:
	bzgrep ^FastReport Result/Log_*.bz2 | awk '{if($$18 != "" && $$19 == "") print $$18,$$2,$$4}' | grep hlt | bzip2 > HLTTimingAll.txt.bz2

CollectTimingPath:
	bzgrep ^FastReport Result/Log_*.bz2 | awk '{if($$18 != "" && $$19 == "") print $$18,$$2,$$4}' | grep HLT | bzip2 > HLTTimingPathAll.txt.bz2

PrintTiming:
	CompileRootMacro AverageTiming.cpp RunTiming
	bzcat HLTTimingAll.txt.bz2 | ./RunTiming | sort -n

PrintTimingPath:
	CompileRootMacro AverageTiming.cpp RunTiming
	bzcat HLTTimingPathAll.txt.bz2 | ./RunTiming | sort -n
