cp Samples/FitResults_30.root FitXD.root

root -l -b -q "CollectResult.C+(\"FitXD.root\", 4.6009, 0.73353, 0, 4999)"



