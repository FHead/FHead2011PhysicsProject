# Part 3: NoJEC x Unfold x Weighted

Z2Smear="\"Samples/Z2SmearingMatrix\""
D6TSmear="\"Samples/D6TSmearingMatrix\""
PythiaZ2Smear="\"Samples/PythiaZ2SmearingMatrix\""

# Part 3-2: D6T

DHFile="\"Samples/NoJEC_D6TUnfold_Weighted.dh\""
Input="\"Samples/data_w30.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $D6TSmear, 0.05)"

# Part 3-3: Pythia

DHFile="\"Samples/NoJEC_PythiaZ2Unfold_Weighted.dh\""
Input="\"Samples/data_w30.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $PythiaZ2Smear, 0.05)"




