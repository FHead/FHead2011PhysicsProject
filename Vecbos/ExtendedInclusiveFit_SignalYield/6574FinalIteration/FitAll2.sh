#!/bin/sh

PF15Smear="\"Samples/PF15SmearingMatrix\""
PF30Smear="\"Samples/PF30SmearingMatrix\""
NoSmear="\"Samples/UnitMatrix\""

# JEC Plus, Unfold, Normal weight
Data="\"Samples/data-w15_JECP.root\""
DHFile="\"Samples/JECPlus_Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 15, $DHFile, true, $PF15Smear)"
Data="\"Samples/data-w30_JECP.root\""
DHFile="\"Samples/JECPlus_Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear)"

mv FinalPlot* JECPlus_Unfold_Weighted/
mv Result* JECPlus_Unfold_Weighted/
mv FitResult* JECPlus_Unfold_Weighted/
mv FitPlot* JECPlus_Unfold_Weighted/
mv Summary* JECPlus_Unfold_Weighted/

# JEC Minus, Unfold, Normal weight
Data="\"Samples/data-w15_JECM.root\""
DHFile="\"Samples/JECMinus_Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 15, $DHFile, true, $PF15Smear)"
Data="\"Samples/data-w30_JECM.root\""
DHFile="\"Samples/JECMinus_Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear)"

mv FinalPlot* JECMinus_Unfold_Weighted/
mv Result* JECMinus_Unfold_Weighted/
mv FitResult* JECMinus_Unfold_Weighted/
mv FitPlot* JECMinus_Unfold_Weighted/
mv Summary* JECMinus_Unfold_Weighted/




















