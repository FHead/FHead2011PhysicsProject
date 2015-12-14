for i in Calo PF
do
   root -l -b -q "FitZPeak.C+(\"Samples/DataAll.root\", \"DataFitNormalIsolation\", \"$i\", 0.3, 30)"
   root -l -b -q "FitZPeak.C+(\"Samples/DataAll.root\", \"DataFitTightIsolation\", \"$i\", 0.05, 30)"
done

for i in UncorrectedCalo Track
do
   root -l -b -q "FitZPeak.C+(\"Samples/DataAll.root\", \"DataFitNormalIsolation\", \"$i\", 0.3, 20)"
   root -l -b -q "FitZPeak.C+(\"Samples/DataAll.root\", \"DataFitTightIsolation\", \"$i\", 0.05, 20)"
done

for i in 15 20 25 40 50
do
   root -l -b -q "FitZPeak.C+(\"Samples/DataAll.root\", \"DataFitNormalIsolation\", \"PF\", 0.3, $i)"
   root -l -b -q "FitZPeak.C+(\"Samples/DataAll.root\", \"DataFitTightIsolation\", \"PF\", 0.05, $i)"
done


