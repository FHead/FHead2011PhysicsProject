#!/bin/sh

PF15Smear="\"Samples/PF15SmearingMatrix\""
PF30Smear="\"Samples/PF30SmearingMatrix\""
NoSmear="\"Samples/UnitMatrix\""

# No JEC, unfold, No weight
# Data="\"Samples/data_w15.root\""
# DHFile="\"Samples/NoJEC_Unfold_Unweighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 15, $DHFile, false, $PF15Smear)"
# Data="\"Samples/data_w30.root\""
# DHFile="\"Samples/NoJEC_Unfold_Unweighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, false, $PF30Smear)"

# mv FinalPlot* NoJEC_Unfold_Unweighted/
# mv Result* NoJEC_Unfold_Unweighted/
# mv FitResult* NoJEC_Unfold_Unweighted/
# mv FitPlot* NoJEC_Unfold_Unweighted/
# mv Summary* NoJEC_Unfold_Unweighted/

# No JEC, unfold, Normal weight
# Data="\"Samples/data_w15.root\""
# DHFile="\"Samples/NoJEC_Unfold_Weighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 15, $DHFile, true, $PF15Smear)"
Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear)"

mv FinalPlot* NoJEC_Unfold_Weighted/
mv Result* NoJEC_Unfold_Weighted/
mv FitResult* NoJEC_Unfold_Weighted/
mv FitPlot* NoJEC_Unfold_Weighted/
mv Summary* NoJEC_Unfold_Weighted/

exit

# No JEC, unfold, Weight +
Data="\"Samples/data_w15P.root\""
DHFile="\"Samples/NoJEC_Unfold_WeightPlus.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 15, $DHFile, true, $PF15Smear)"
Data="\"Samples/data_w30P.root\""
DHFile="\"Samples/NoJEC_Unfold_WeightPlus.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear)"

mv FinalPlot* NoJEC_Unfold_WeightPlus/
mv Result* NoJEC_Unfold_WeightPlus/
mv FitResult* NoJEC_Unfold_WeightPlus/
mv FitPlot* NoJEC_Unfold_WeightPlus/
mv Summary* NoJEC_Unfold_WeightPlus/

# No JEC, unfold, Weight -
Data="\"Samples/data_w15M.root\""
DHFile="\"Samples/NoJEC_Unfold_WeightMinus.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 15, $DHFile, true, $PF15Smear)"
Data="\"Samples/data_w30M.root\""
DHFile="\"Samples/NoJEC_Unfold_WeightMinus.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear)"

mv FinalPlot* NoJEC_Unfold_WeightMinus/
mv Result* NoJEC_Unfold_WeightMinus/
mv FitResult* NoJEC_Unfold_WeightMinus/
mv FitPlot* NoJEC_Unfold_WeightMinus/
mv Summary* NoJEC_Unfold_WeightMinus/










