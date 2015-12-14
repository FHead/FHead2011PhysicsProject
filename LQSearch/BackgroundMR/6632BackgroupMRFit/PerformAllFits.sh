#!/bin/sh

for i in 0 1 2 3
do
   # ./PerformFit CopiedFromT3SUSY_QCD_2jet_120to280 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_2jet_280to500 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_2jet_40to120 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_2jet_500to5000 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_3jet_120to280 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_3jet_280to500 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_3jet_40to120 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_3jet_500to5000 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_4jet_120to280 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_4jet_280to500 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_4jet_40to120 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_4jet_500to5000 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_5jet_120to280 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_5jet_280to500 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_5jet_40to120 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_5jet_500to5000 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_6jet_120to280 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_6jet_280to500 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_6jet_40to120 100 $i
   # ./PerformFit CopiedFromT3SUSY_QCD_6jet_500to5000 100 $i
   ./PerformFit DYJetsToLL_TuneD6T_M-10To50_7TeV-madgraph-tauola 100 $i
   ./PerformFit DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola 90 $ii
   ./PerformFit DYJetsToLL_TuneZ2_M-50_madgraph 90 $i
   ./PerformFit QCD_Pt-20to30_BCtoE_TuneZ2 75 $i
   ./PerformFit QCD_Pt-30to80_BCtoE_TuneZ2 80 $i   # Boundary statistics
   ./PerformFit QCD_Pt-80to170_BCtoE_TuneZ2 80 $i   # Boundary statistics
   ./PerformFit TTJets 150 $i
   ./PerformFit TTJets_TuneD6T 150 $i
   ./PerformFit TToBLNu_s 150 $i
   ./PerformFit TToBLNu_t 150 $i
   ./PerformFit TToBLNu_TuneZ2_s-channel_7TeV-madgraph 150 $i
   ./PerformFit TToBLNu_TuneZ2_t-channel_7TeV-madgraph 150 $i
   ./PerformFit TToBLNu_TuneZ2_tW-channel_7TeV-madgraph 150 $i
   ./PerformFit TToBLNu_tW 150 $i
   # ./PerformFit WJetsToLNu_madgraph 90 $i --double
   # ./PerformFit WJetsToLNu_TuneD6T_7TeV-madgraph-tauola 90 $i --double
   # ./PerformFit WJetsToLNu_TuneD6T_madgraph 90 $i --double
   # ./PerformFit WJetsToLNu_TuneZ2_7TeV-madgraph-tauola 90 $i --double
   # ./PerformFit WWTo2L2Nu 90 $i --double
   # ./PerformFit WWTo2L2Nu_TuneZ2 90 $i --double
   # ./PerformFit WWtoAnything 110 $i --double
   # ./PerformFit WZTo3LNu_TuneZ2 100 $i --double
   # ./PerformFit WZtoAnything_TuneZ2_PU 110 $i --double
   # ./PerformFit WZtoAnything_TuneZ2 110 $i --double
   ./PerformFit ZJetsToLL_madgraph 90 $i
   ./PerformFit ZJetsToLL_TuneD6T_madgraph 90 $i
   # ./PerformFit ZnunuMADGRAPH 50 $i   # No statistics at all
   ./PerformFit ZZtoAnything_TuneZ2 100 $i
done

