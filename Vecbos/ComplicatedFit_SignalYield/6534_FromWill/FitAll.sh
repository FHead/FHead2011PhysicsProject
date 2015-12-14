#!/bin/sh

# root -l -b -q "SimultaneousFit.C+(\"Samples/data_ZMT.root\", 4, \"pf\", 15, \"Samples/data_ZMT-nocut.dh\", false)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_ZMT.root\", 4, \"pf\", 30, \"Samples/data_ZMT-nocut.dh\", false)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_ZMT.root\", 4, \"pf\", 15, \"Samples/data_ZMT-mtcut.dh\", true)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_ZMT.root\", 4, \"pf\", 30, \"Samples/data_ZMT-mtcut.dh\", true)"

# mkdir data_ZMT
# mv ResultPlot* data_ZMT/
# mv ComplicatedFit* data_ZMT/
# mv FitYields* data_ZMT/

# root -l -b -q "SimultaneousFit.C+(\"Samples/zjets-sara.root\", 4, \"pf\", 15, \"Samples/zjets-sara-nocut.dh\", false)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/zjets-sara.root\", 4, \"pf\", 30, \"Samples/zjets-sara-nocut.dh\", false)"
root -l -b -q "SimultaneousFit.C+(\"Samples/zjets-sara.root\", 4, \"pf\", 15, \"Samples/zjets-sara-mtcut.dh\", true)"
root -l -b -q "SimultaneousFit.C+(\"Samples/zjets-sara.root\", 4, \"pf\", 30, \"Samples/zjets-sara-mtcut.dh\", true)"

mkdir zjets-sara
mv ResultPlot* zjets-sara/
mv ComplicatedFit* zjets-sara/
mv FitYields* zjets-sara/





