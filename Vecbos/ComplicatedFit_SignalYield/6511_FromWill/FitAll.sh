#!/bin/sh

root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, \"Samples/data_w15_weighted.dh\", true)"
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, \"Samples/data_w15_unweighted.dh\", false)"

root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, \"Samples/data_w30_weighted.dh\", true)"
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, \"Samples/data_w30_unweighted.dh\", false)"

mv ResultPlot* Normal/
mv ComplicatedFit* Normal/
mv FitYields* Normal/

root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15P.root\", 4, \"pf\", 15, \"Samples/data_w15P_weighted.dh\", true)"
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15P.root\", 4, \"pf\", 15, \"Samples/data_w15P_unweighted.dh\", false)"

root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30P.root\", 4, \"pf\", 30, \"Samples/data_w30P_weighted.dh\", true)"
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30P.root\", 4, \"pf\", 30, \"Samples/data_w30P_unweighted.dh\", false)"

mv ResultPlot* Plus/
mv ComplicatedFit* Plus/
mv FitYields* Plus/

root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15M.root\", 4, \"pf\", 15, \"Samples/data_w15M_weighted.dh\", true)"
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15M.root\", 4, \"pf\", 15, \"Samples/data_w15M_unweighted.dh\", false)"

root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30M.root\", 4, \"pf\", 30, \"Samples/data_w30M_weighted.dh\", true)"
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30M.root\", 4, \"pf\", 30, \"Samples/data_w30M_unweighted.dh\", false)"

mv ResultPlot* Minus/
mv ComplicatedFit* Minus/
mv FitYields* Minus/





