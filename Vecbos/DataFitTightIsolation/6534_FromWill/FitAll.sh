Input="\"Samples/zjets-sara.root\""
DHFile="\"Samples/zjets-sara-nocut.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 15, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 15, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 15, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 15, $DHFile, 0, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 30, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 30, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 30, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 30, $DHFile, 0, false)"

Input="\"Samples/zjets-sara.root\""
DHFile="\"Samples/zjets-sara-mtcut.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationC\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationC\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationC\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationC\", \"pf\", 0.05, 15, $DHFile, 0, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationC\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationC\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationC\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationC\", \"pf\", 0.05, 30, $DHFile, 0, true)"



Input="\"Samples/data_ZMT.root\""
DHFile="\"Samples/data_ZMT-nocut.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 15, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 15, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 15, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 15, $DHFile, 0, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 30, $DHFile, 1, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 30, $DHFile, 1, false)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 30, $DHFile, 0, false)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 30, $DHFile, 0, false)"

Input="\"Samples/data_ZMT.root\""
DHFile="\"Samples/data_ZMT-mtcut.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationC\", \"pf\", 9999, 15, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationC\", \"pf\", 0.05, 15, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationC\", \"pf\", 9999, 15, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationC\", \"pf\", 0.05, 15, $DHFile, 0, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationC\", \"pf\", 9999, 30, $DHFile, 1, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationC\", \"pf\", 0.05, 30, $DHFile, 1, true)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolationC\", \"pf\", 9999, 30, $DHFile, 0, true)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolationC\", \"pf\", 0.05, 30, $DHFile, 0, true)"



