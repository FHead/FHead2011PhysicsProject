Input="\"Samples/DataAll.root\""
DHFile="\"Samples/DataAll.dh\""

for i in 15 16 17 18 19 20 22 24 26 28 30 35 40 50
do
   for j in PF Calo
   do
      for k in "\"_Eta24\"" "\"\"" "\"_Eta10\""
      do
         # root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"$j\", 0.3, $i, $DHFile, $k)"
         date
         root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"$j\", 0.05, $i, $DHFile, $k)"
         date
      done
   done
done

# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"Track\", 0.3, 20, $DHFile)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"Track\", 0.05, 20, $DHFile)"
# root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"UncorrectedCalo\", 0.3, 20, $DHFile)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"UncorrectedCalo\", 0.05, 20, $DHFile)"




