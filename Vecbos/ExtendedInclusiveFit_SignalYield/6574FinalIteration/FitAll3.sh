#!/bin/sh

Z215Smear="\"Samples/Z215SmearingMatrix\""
Z230Smear="\"Samples/Z230SmearingMatrix\""
D6T15Smear="\"Samples/D6T15SmearingMatrix\""
D6T30Smear="\"Samples/D6T30SmearingMatrix\""
Pythia15Smear="\"Samples/Pythia15SmearingMatrix\""
Pythia30Smear="\"Samples/Pythia30SmearingMatrix\""
NoSmear="\"Samples/UnitMatrix\""

# No JEC, unfold, Normal weight
Data="\"Samples/data_w15.root\""
DHFile="\"Samples/NoJEC_Z2Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 15, $DHFile, true, $Z215Smear)"
Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_Z2Unfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $Z230Smear)"

mv FinalPlot* NoJEC_Z2Unfold_Weighted/
mv Result* NoJEC_Z2Unfold_Weighted/
mv FitResult* NoJEC_Z2Unfold_Weighted/
mv FitPlot* NoJEC_Z2Unfold_Weighted/
mv Summary* NoJEC_Z2Unfold_Weighted/



# No JEC, unfold, Normal weight
Data="\"Samples/data_w15.root\""
DHFile="\"Samples/NoJEC_D6TUnfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 15, $DHFile, true, $D6T15Smear)"
Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_D6TUnfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $D6T30Smear)"

mv FinalPlot* NoJEC_D6TUnfold_Weighted/
mv Result* NoJEC_D6TUnfold_Weighted/
mv FitResult* NoJEC_D6TUnfold_Weighted/
mv FitPlot* NoJEC_D6TUnfold_Weighted/
mv Summary* NoJEC_D6TUnfold_Weighted/



# No JEC, unfold, Normal weight
Data="\"Samples/data_w15.root\""
DHFile="\"Samples/NoJEC_PythiaUnfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 15, $DHFile, true, $Pythia15Smear)"
Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_PythiaUnfold_Weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+($Data, 4, \"pf\", 30, $DHFile, true, $Pythia30Smear)"

mv FinalPlot* NoJEC_PythiaUnfold_Weighted/
mv Result* NoJEC_PythiaUnfold_Weighted/
mv FitResult* NoJEC_PythiaUnfold_Weighted/
mv FitPlot* NoJEC_PythiaUnfold_Weighted/
mv Summary* NoJEC_PythiaUnfold_Weighted/
























