Input="\"Samples/DataAllTrimmedStage2.root\""
DHFile="\"Samples/DataAll.dh\""

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"Calo\", 9999, 15, $DHFile, 1)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"Calo\", 0.05, 15, $DHFile, 1)"

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"Calo\", 9999, 15, $DHFile, 0)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"Calo\", 0.05, 15, $DHFile, 0)"

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"Calo\", 9999, 30, $DHFile, 1)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"Calo\", 0.05, 30, $DHFile, 1)"

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"Calo\", 9999, 30, $DHFile, 0)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"Calo\", 0.05, 30, $DHFile, 0)"


# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"PF\", 9999, 15, $DHFile, 1)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"PF\", 0.05, 15, $DHFile, 1)"

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"PF\", 9999, 15, $DHFile, 0)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"PF\", 0.05, 15, $DHFile, 0)"

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"PF\", 9999, 30, $DHFile, 1)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"PF\", 0.05, 30, $DHFile, 1)"

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"PF\", 9999, 30, $DHFile, 0)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"PF\", 0.05, 30, $DHFile, 0)"



# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"Track\", 9999, 20, $DHFile, 1)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"Track\", 0.05, 20, $DHFile, 1)"

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"Track\", 9999, 20, $DHFile, 0)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"Track\", 0.05, 20, $DHFile, 0)"


# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"UncorrectedCalo\", 9999, 20, $DHFile, 1)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"UncorrectedCalo\", 0.05, 20, $DHFile, 1)"

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"UncorrectedCalo\", 9999, 20, $DHFile, 0)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"UncorrectedCalo\", 0.05, 20, $DHFile, 0)"


for i in `seq 15 50`
do
   root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"PF\", 9999, $i, $DHFile, 1)"
   root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"PF\", 0.05, $i, $DHFile, 1)"

   root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"PF\", 9999, $i, $DHFile, 0)"
   root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"PF\", 0.05, $i, $DHFile, 0)"
done




