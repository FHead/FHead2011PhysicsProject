Input="\"Samples/DataAll.root\""
DHFile="\"Samples/DataAll.dh\""

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 30, $DHFile)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 30, $DHFile)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 15, $DHFile)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 15, $DHFile)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 30, $DHFile, 0)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 30, $DHFile, 0)"

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"pf\", 9999, 15, $DHFile, 0)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"pf\", 0.05, 15, $DHFile, 0)"



