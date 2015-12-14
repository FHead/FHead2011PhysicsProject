PF30Smear="\"Samples/PF30SmearingMatrix\""

DHFile="\"Samples/NoJEC_Unfold_Weighted.dh\""

Input="\"Samples/data_w30.root\""
root -l -b -q "FitZPeak.C+($Input, 4, \"pf\", 30, $DHFile, true, $PF30Smear, 0.05)"




