#!/bin/sh

Z2Smear="\"Samples/Z2SmearingMatrix\""
NoSmear="\"Samples/UnitMatrix\""

# Dimensions: NoJEC x Unfold/NoUnfold x Unweighted/WeightMinus/Weight/WeightPlus

# Unweighted - 15 (100, 10) [C0]  30 (30 10) [C0]
Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_Unfold_Unweighted.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, false, $Z2Smear)"
mv ComplicatedFit* NoJEC_Unfold_Unweighted/
mv FitYields* NoJEC_Unfold_Unweighted/
mv ResultPlots* NoJEC_Unfold_Unweighted/
mv UnfoldedResult* NoJEC_Unfold_Unweighted/

# Normal weight
Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $Z2Smear)"
mv ComplicatedFit* NoJEC_Unfold_Weighted/
mv FitYields* NoJEC_Unfold_Weighted/
mv ResultPlots* NoJEC_Unfold_Weighted/
mv UnfoldedResult* NoJEC_Unfold_Weighted/

# Weight plus - 15 (100, 10) [C01]  30 (500, 10) [C01]
Data="\"Samples/data_w30P.root\""
DHFile="\"Samples/NoJEC_Unfold_WeightPlus.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $Z2Smear)"
mv ComplicatedFit* NoJEC_Unfold_WeightPlus/
mv FitYields* NoJEC_Unfold_WeightPlus/
mv ResultPlots* NoJEC_Unfold_WeightPlus/
mv UnfoldedResult* NoJEC_Unfold_WeightPlus/

# Weight minus - 15 (100, 10) [C01]  30 (500, 10) [C01]
Data="\"Samples/data_w30M.root\""
DHFile="\"Samples/NoJEC_Unfold_WeightMinus.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $Z2Smear)"
mv ComplicatedFit* NoJEC_Unfold_WeightMinus/
mv FitYields* NoJEC_Unfold_WeightMinus/
mv ResultPlots* NoJEC_Unfold_WeightMinus/
mv UnfoldedResult* NoJEC_Unfold_WeightMinus/










