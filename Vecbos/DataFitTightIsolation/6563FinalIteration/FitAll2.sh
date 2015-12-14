
# Part 2: JECPlus/JECMinus x Unfold x Weighted

Input="\"Samples/data-w15_JECP.root\""
DHFile="\"Samples/JECPlus_NoUnfold_Weighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWJECP\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWJECP\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWJECP\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWJECP\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data-w30_JECP.root\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWJECP\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWJECP\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWJECP\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWJECP\", \"pf\", 0.05, 30, $DHFile, 0, true)"



Input="\"Samples/data-w15_JECM.root\""
DHFile="\"Samples/JECMinus_NoUnfold_Weighted.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWJECM\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWJECM\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWJECM\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWJECM\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data-w30_JECM.root\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWJECM\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWJECM\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationWJECM\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationWJECM\", \"pf\", 0.05, 30, $DHFile, 0, true)"




