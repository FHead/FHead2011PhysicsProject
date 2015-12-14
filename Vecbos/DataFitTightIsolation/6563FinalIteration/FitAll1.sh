# Part 1: NoJEC x Unfold/NoUnfold x Unweighted/WeightPlus/Weighted/WeightMinus

# Part 1-1: NoJEC x Unfold/NoUnfold x Weighted

Input="\"Samples/data_w15.root\""
DHFile="\"Samples/NoJEC_NoUnfold_Weighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationW\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationW\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationW\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationW\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data_w30.root\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationW\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationW\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationW\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationW\", \"pf\", 0.05, 30, $DHFile, 0, true)"

cp Samples/NoJEC_NoUnfold_Weighted.dh Samples/NoJEC_Unfold_Weighted.dh


# Part 1-2: NoJEC x Unfold/NoUnfold x Unweighted

Input="\"Samples/data_w15.root\""
DHFile="\"Samples/NoJEC_NoUnfold_Unweighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationU\", \"pf\", 9999, 15, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationU\", \"pf\", 0.05, 15, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationU\", \"pf\", 9999, 15, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationU\", \"pf\", 0.05, 15, $DHFile, 0, false)"

Input="\"Samples/data_w30.root\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationU\", \"pf\", 9999, 30, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationU\", \"pf\", 0.05, 30, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationU\", \"pf\", 9999, 30, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationU\", \"pf\", 0.05, 30, $DHFile, 0, false)"

cp Samples/NoJEC_NoUnfold_Unweighted.dh Samples/NoJEC_Unfold_Unweighted.dh


# Part 1-3: NoJEC x Unfold/NoUnfold x WeightPlus

Input="\"Samples/data_w15P.root\""
DHFile="\"Samples/NoJEC_NoUnfold_WeightPlus.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWP\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWP\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWP\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWP\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data_w30P.root\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWP\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWP\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWP\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWP\", \"pf\", 0.05, 30, $DHFile, 0, true)"

cp Samples/NoJEC_NoUnfold_WeightPlus.dh Samples/NoJEC_Unfold_WeightPlus.dh


# Part 1-4: NoJEC x Unfold/NoUnfold x WeightMinus

Input="\"Samples/data_w15M.root\""
DHFile="\"Samples/NoJEC_NoUnfold_WeightMinus.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWM\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWM\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWM\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWM\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data_w30M.root\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWM\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWM\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWM\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWM\", \"pf\", 0.05, 30, $DHFile, 0, true)"

cp Samples/NoJEC_NoUnfold_WeightMinus.dh Samples/NoJEC_Unfold_WeightMinus.dh




