Z2Smear="\"Samples/Z2SmearingMatrix\""
D6TSmear="\"Samples/D6TSmearingMatrix\""
PythiaZ2Smear="\"Samples/PythiaZ2SmearingMatrix\""


# Part 2: JECPlus/JECMinus x Unfold x Weighted

DHFile="\"Samples/JECPlus_Unfold_Weighted.dh\""
Input="\"Samples/data-w30_JECP.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $Z2Smear, 0.05)"



DHFile="\"Samples/JECMinus_Unfold_Weighted.dh\""
Input="\"Samples/data-w30_JECM.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $Z2Smear, 0.05)"





