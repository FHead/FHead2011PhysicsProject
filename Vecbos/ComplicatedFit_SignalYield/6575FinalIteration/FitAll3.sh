#!/bin/sh

Z215Smear="\"Samples/Z215SmearingMatrix\""
Z230Smear="\"Samples/Z230SmearingMatrix\""
D6T15Smear="\"Samples/D6T15SmearingMatrix\""
D6T30Smear="\"Samples/D6T30SmearingMatrix\""
Pythia15Smear="\"Samples/Pythia15SmearingMatrix\""
Pythia30Smear="\"Samples/Pythia30SmearingMatrix\""
NoSmear="\"Samples/UnitMatrix\""

# Dimensions: NoJEC x Unfold (Different ones) x Weighted

# Data="\"Samples/data_w15.root\""
# DHFile="\"Samples/NoJEC_Z2Unfold_Weighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, true, $Z215Smear)"
# mv ComplicatedFit* NoJEC_Z2Unfold_Weighted/
# mv FitYields* NoJEC_Z2Unfold_Weighted/
# mv ResultPlots* NoJEC_Z2Unfold_Weighted/
# mv UnfoldedResult* NoJEC_Z2Unfold_Weighted/

# Data="\"Samples/data_w30.root\""
# DHFile="\"Samples/NoJEC_Z2Unfold_Weighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $Z230Smear)"
# mv ComplicatedFit* NoJEC_Z2Unfold_Weighted/
# mv FitYields* NoJEC_Z2Unfold_Weighted/
# mv ResultPlots* NoJEC_Z2Unfold_Weighted/
# mv UnfoldedResult* NoJEC_Z2Unfold_Weighted/



# Data="\"Samples/data_w15.root\""
# DHFile="\"Samples/NoJEC_D6TUnfold_Weighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, true, $D6T15Smear)"
# mv ComplicatedFit* NoJEC_D6TUnfold_Weighted/
# mv FitYields* NoJEC_D6TUnfold_Weighted/
# mv ResultPlots* NoJEC_D6TUnfold_Weighted/
# mv UnfoldedResult* NoJEC_D6TUnfold_Weighted/

Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_D6TUnfold_Weighted.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $D6T30Smear)"
mv ComplicatedFit* NoJEC_D6TUnfold_Weighted/
mv FitYields* NoJEC_D6TUnfold_Weighted/
mv ResultPlots* NoJEC_D6TUnfold_Weighted/
mv UnfoldedResult* NoJEC_D6TUnfold_Weighted/


exit

Data="\"Samples/data_w15.root\""
DHFile="\"Samples/NoJEC_PythiaUnfold_Weighted.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, true, $Pythia15Smear)"
mv ComplicatedFit* NoJEC_PythiaUnfold_Weighted/
mv FitYields* NoJEC_PythiaUnfold_Weighted/
mv ResultPlots* NoJEC_PythiaUnfold_Weighted/
mv UnfoldedResult* NoJEC_PythiaUnfold_Weighted/

Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_PythiaUnfold_Weighted.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $Pythia30Smear)"
mv ComplicatedFit* NoJEC_PythiaUnfold_Weighted/
mv FitYields* NoJEC_PythiaUnfold_Weighted/
mv ResultPlots* NoJEC_PythiaUnfold_Weighted/
mv UnfoldedResult* NoJEC_PythiaUnfold_Weighted/






















































































