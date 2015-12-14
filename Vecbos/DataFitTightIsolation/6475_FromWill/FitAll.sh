Input="\"Samples/data_w15.root\""
DHFile="\"Samples/data_w15_weighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationW\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationW\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationW\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationW\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data_w15.root\""
DHFile="\"Samples/data_w15_unweighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationU\", \"pf\", 9999, 15, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationU\", \"pf\", 0.05, 15, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationU\", \"pf\", 9999, 15, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationU\", \"pf\", 0.05, 15, $DHFile, 0, false)"

Input="\"Samples/data_w30.root\""
DHFile="\"Samples/data_w30_weighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationW\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationW\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationW\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationW\", \"pf\", 0.05, 30, $DHFile, 0, true)"

Input="\"Samples/data_w30.root\""
DHFile="\"Samples/data_w30_unweighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationU\", \"pf\", 9999, 30, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationU\", \"pf\", 0.05, 30, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationU\", \"pf\", 9999, 30, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationU\", \"pf\", 0.05, 30, $DHFile, 0, false)"



