
PF15Smear="\"Samples/PF15SmearingMatrix\""
PF30Smear="\"Samples/PF30SmearingMatrix\""

# Part 2: JECPlus/JECMinus x Unfold x Weighted

DHFile="\"Samples/JECPlus_Unfold_Weighted.dh\""

Input="\"Samples/data-w15_JECP.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 15, $DHFile, true, $PF15Smear, 0.05)"

Input="\"Samples/data-w30_JECP.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $PF30Smear, 0.05)"



DHFile="\"Samples/JECMinus_Unfold_Weighted.dh\""

Input="\"Samples/data-w15_JECM.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 15, $DHFile, true, $PF15Smear, 0.05)"

Input="\"Samples/data-w30_JECM.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $PF30Smear, 0.05)"





