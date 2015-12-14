# weighted

Input="\"Samples/data-w15mt_JECM.root\""
DHFile="\"Samples/dataw_JECM.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationM\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationM\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationM\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationM\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data-w30mt_JECM.root\""
DHFile="\"Samples/dataw_JECM.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationM\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationM\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationM\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationM\", \"pf\", 0.05, 30, $DHFile, 0, true)"


Input="\"Samples/data-w15mt_JECP.root\""
DHFile="\"Samples/dataw_JECP.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationP\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationP\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationP\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationP\", \"pf\", 0.05, 15, $DHFile, 0, true)"

Input="\"Samples/data-w30mt_JECP.root\""
DHFile="\"Samples/dataw_JECP.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationP\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationP\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationP\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationP\", \"pf\", 0.05, 30, $DHFile, 0, true)"

mv DataFit* Weighted


# unweighted

Input="\"Samples/data-w15mt_JECM.root\""
DHFile="\"Samples/datau_JECM.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationM\", \"pf\", 9999, 15, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationM\", \"pf\", 0.05, 15, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationM\", \"pf\", 9999, 15, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationM\", \"pf\", 0.05, 15, $DHFile, 0, false)"

Input="\"Samples/data-w30mt_JECM.root\""
DHFile="\"Samples/datau_JECM.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationM\", \"pf\", 9999, 30, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationM\", \"pf\", 0.05, 30, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationM\", \"pf\", 9999, 30, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationM\", \"pf\", 0.05, 30, $DHFile, 0, false)"


Input="\"Samples/data-w15mt_JECP.root\""
DHFile="\"Samples/datau_JECP.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationP\", \"pf\", 9999, 15, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationP\", \"pf\", 0.05, 15, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationP\", \"pf\", 9999, 15, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationP\", \"pf\", 0.05, 15, $DHFile, 0, false)"

Input="\"Samples/data-w30mt_JECP.root\""
DHFile="\"Samples/datau_JECP.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationP\", \"pf\", 9999, 30, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationP\", \"pf\", 0.05, 30, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationP\", \"pf\", 9999, 30, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationP\", \"pf\", 0.05, 30, $DHFile, 0, false)"

mv DataFit* Unweighted

