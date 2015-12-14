#!/bin/sh

Z2Smear="\"Samples/Z2SmearingMatrix\""
NoSmear="\"Samples/UnitMatrix\""

# Dimensions: JECPlus/JECMinus x Unfold x Weight

# JEC Plus
Data="\"Samples/data-w30_JECP.root\""
DHFile="\"Samples/JECPlus_Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $Z2Smear)"
mv ComplicatedFit* JECPlus_Unfold_Weighted/
mv FitYields* JECPlus_Unfold_Weighted/
mv ResultPlots* JECPlus_Unfold_Weighted/
mv UnfoldedResult* JECPlus_Unfold_Weighted/


# JEC Minus
Data="\"Samples/data-w30_JECM.root\""
DHFile="\"Samples/JECMinus_Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $Z2Smear)"
mv ComplicatedFit* JECMinus_Unfold_Weighted/
mv FitYields* JECMinus_Unfold_Weighted/
mv ResultPlots* JECMinus_Unfold_Weighted/
mv UnfoldedResult* JECMinus_Unfold_Weighted/






