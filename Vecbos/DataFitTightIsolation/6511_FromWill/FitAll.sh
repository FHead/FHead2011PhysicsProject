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



Input="\"Samples/data_w15P.root\""
DHFile="\"Samples/data_w15P_weighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWP\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWP\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWP\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWP\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data_w15P.root\""
DHFile="\"Samples/data_w15P_unweighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationUP\", \"pf\", 9999, 15, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationUP\", \"pf\", 0.05, 15, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationUP\", \"pf\", 9999, 15, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationUP\", \"pf\", 0.05, 15, $DHFile, 0, false)"

Input="\"Samples/data_w30P.root\""
DHFile="\"Samples/data_w30P_weighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWP\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWP\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWP\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWP\", \"pf\", 0.05, 30, $DHFile, 0, true)"

Input="\"Samples/data_w30P.root\""
DHFile="\"Samples/data_w30P_unweighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationUP\", \"pf\", 9999, 30, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationUP\", \"pf\", 0.05, 30, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationUP\", \"pf\", 9999, 30, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationUP\", \"pf\", 0.05, 30, $DHFile, 0, false)"



Input="\"Samples/data_w15M.root\""
DHFile="\"Samples/data_w15M_weighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWM\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWM\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWM\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWM\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data_w15M.root\""
DHFile="\"Samples/data_w15M_unweighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationUM\", \"pf\", 9999, 15, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationUM\", \"pf\", 0.05, 15, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationUM\", \"pf\", 9999, 15, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationUM\", \"pf\", 0.05, 15, $DHFile, 0, false)"

Input="\"Samples/data_w30M.root\""
DHFile="\"Samples/data_w30M_weighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWM\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWM\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWM\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWM\", \"pf\", 0.05, 30, $DHFile, 0, true)"

Input="\"Samples/data_w30M.root\""
DHFile="\"Samples/data_w30M_unweighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationUM\", \"pf\", 9999, 30, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationUM\", \"pf\", 0.05, 30, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationUM\", \"pf\", 9999, 30, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationUM\", \"pf\", 0.05, 30, $DHFile, 0, false)"



