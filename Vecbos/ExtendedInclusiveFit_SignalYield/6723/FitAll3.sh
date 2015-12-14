#!/bin/sh

D6TSmear="\"Samples/D6TSmearingMatrix\""
PythiaSmear="\"Samples/PythiaZ2SmearingMatrix\""
NoSmear="\"Samples/UnitMatrix\""

Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_D6TUnfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $D6TSmear)"

mv FinalPlot* NoJEC_D6TUnfold_Weighted/
mv Result* NoJEC_D6TUnfold_Weighted/
mv FitResult* NoJEC_D6TUnfold_Weighted/
mv FitPlot* NoJEC_D6TUnfold_Weighted/
mv Summary* NoJEC_D6TUnfold_Weighted/



Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_PythiaZ2Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $PythiaSmear)"

mv FinalPlot* NoJEC_PythiaZ2Unfold_Weighted/
mv Result* NoJEC_PythiaZ2Unfold_Weighted/
mv FitResult* NoJEC_PythiaZ2Unfold_Weighted/
mv FitPlot* NoJEC_PythiaZ2Unfold_Weighted/
mv Summary* NoJEC_PythiaZ2Unfold_Weighted/
























