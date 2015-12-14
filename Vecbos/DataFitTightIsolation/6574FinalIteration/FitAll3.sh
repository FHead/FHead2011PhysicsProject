# Part 3: NoJEC x Unfold x Weighted

Z215Smear="\"Samples/Z215SmearingMatrix\""
Z230Smear="\"Samples/Z230SmearingMatrix\""
D6T15Smear="\"Samples/D6T15SmearingMatrix\""
D6T30Smear="\"Samples/D6T30SmearingMatrix\""
Pythia15Smear="\"Samples/Pythia15SmearingMatrix\""
Pythia30Smear="\"Samples/Pythia30SmearingMatrix\""

# Part 3-1: Z2

DHFile="\"Samples/NoJEC_Z2Unfold_Weighted.dh\""

Input="\"Samples/data_w15.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 15, $DHFile, true, $Z215Smear, 0.05)"

Input="\"Samples/data_w30.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $Z230Smear, 0.05)"

# Part 3-2: D6T

DHFile="\"Samples/NoJEC_D6TUnfold_Weighted.dh\""

Input="\"Samples/data_w15.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 15, $DHFile, true, $D6T15Smear, 0.05)"

Input="\"Samples/data_w30.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $D6T30Smear, 0.05)"

# Part 3-3: Pythia

DHFile="\"Samples/NoJEC_PythiaUnfold_Weighted.dh\""

Input="\"Samples/data_w15.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 15, $DHFile, true, $Pythia15Smear, 0.05)"

Input="\"Samples/data_w30.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $Pythia30Smear, 0.05)"




