for i in Calo UncorrectedCalo Track PF
do
   root -l -b -q "FitZPeak.C+(\"Samples/DataAll.root\", \"DataFitNormalIsolation\", \"$i\", 0.3)"
   root -l -b -q "FitZPeak.C+(\"Samples/DataAll.root\", \"DataFitTightIsolation\", \"$i\", 0.05)"
   # root -l -b -q "FitZPeak.C+(\"Samples/ZJetsAll.root\", \"MCFitTightIsolation\", \"$i\", 0.05)"
   # root -l -b -q "FitZPeak.C+(\"Samples/ZJetsAll.root\", \"MCFitNormalIsolation\", \"$i\", 0.3)"
done



