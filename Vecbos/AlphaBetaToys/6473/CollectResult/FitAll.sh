cp Samples/FitResults_30.root FitXD.root

root -l -b -q "CollectResult.C+(\"FitXD.root\", 5.3912, 0, 4999)"



