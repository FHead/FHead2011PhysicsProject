Input="\"Samples/DataAll.root\""
DHFile="\"Samples/DataAll.dh\""

for i in 15 17 20 25 30 40 50
do
   for j in PF Calo
   do
      for k in "\"_Eta10\"" "\"_Eta24\"" "\"\""
      do
         root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"$j\", 0.3, $i, $DHFile, $k)"
         root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"$j\", 0.05, $i, $DHFile, $k)"
      done
   done
done

root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"Track\", 0.3, 20, $DHFile)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"Track\", 0.05, 20, $DHFile)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitNormalIsolation\", \"UncorrectedCalo\", 0.3, 20, $DHFile)"
root -l -b -q "FitZPeak.C+($Input, \"DataFitTightIsolation\", \"UncorrectedCalo\", 0.05, 20, $DHFile)"




