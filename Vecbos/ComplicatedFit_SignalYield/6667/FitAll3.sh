#!/bin/sh

Z2Smear="\"Samples/Z2SmearingMatrix\""
D6TSmear="\"Samples/D6TSmearingMatrix\""
PythiaZ2Smear="\"Samples/PythiaZ2SmearingMatrix\""
NoSmear="\"Samples/UnitMatrix\""

# Dimensions: NoJEC x Unfold (Different ones) x Weighted

# Data="\"Samples/data_w30.root\""
# DHFile="\"Samples/NoJEC_D6TUnfold_Weighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $D6TSmear)"
# mv ComplicatedFit* NoJEC_D6TUnfold_Weighted/
# mv FitYields* NoJEC_D6TUnfold_Weighted/
# mv ResultPlots* NoJEC_D6TUnfold_Weighted/
# mv UnfoldedResult* NoJEC_D6TUnfold_Weighted/


Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_PythiaZ2Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $PythiaZ2Smear)"
mv ComplicatedFit* NoJEC_PythiaZ2Unfold_Weighted/
mv FitYields* NoJEC_PythiaZ2Unfold_Weighted/
mv ResultPlots* NoJEC_PythiaZ2Unfold_Weighted/
mv UnfoldedResult* NoJEC_PythiaZ2Unfold_Weighted/





