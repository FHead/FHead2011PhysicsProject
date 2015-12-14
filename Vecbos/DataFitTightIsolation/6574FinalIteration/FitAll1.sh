# Part 1: NoJEC x Unfold x Unweighted/WeightPlus/Weighted/WeightMinus

PF15Smear="\"Samples/PF15SmearingMatrix\""
PF30Smear="\"Samples/PF30SmearingMatrix\""

# Part 1-1: NoJEC x Unfold x Weighted

DHFile="\"Samples/NoJEC_Unfold_Weighted.dh\""

Input="\"Samples/data_w15.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 15, $DHFile, true, $PF15Smear, 0.05)"

Input="\"Samples/data_w30.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $PF30Smear, 0.05)"

# Part 1-2: NoJEC x Unfold x Unweighted

DHFile="\"Samples/NoJEC_Unfold_Unweighted.dh\""

Input="\"Samples/data_w15.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 15, $DHFile, false, $PF15Smear, 0.05)"

Input="\"Samples/data_w30.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, false, $PF30Smear, 0.05)"

# Part 1-3: NoJEC x Unfold x WeightPlus

DHFile="\"Samples/NoJEC_Unfold_WeightPlus.dh\""

Input="\"Samples/data_w15P.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 15, $DHFile, true, $PF15Smear, 0.05)"

Input="\"Samples/data_w30P.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $PF30Smear, 0.05)"

# Part 1-4: NoJEC x Unfold x WeightMinus

DHFile="\"Samples/NoJEC_Unfold_WeightMinus.dh\""

Input="\"Samples/data_w15M.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 15, $DHFile, true, $PF15Smear, 0.05)"

Input="\"Samples/data_w30M.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $PF30Smear, 0.05)"






