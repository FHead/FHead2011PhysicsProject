#!/bin/sh

DHFile="\"Samples/data_ZMT-nocut.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_ZMT.root\", 4, \"pf\", 30, $DHFile, false)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_ZMT.root\", 4, \"pf\", 15, $DHFile, false)"

DHFile="\"Samples/data_ZMT-mtcut.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_ZMT.root\", 4, \"pf\", 30, $DHFile, true)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_ZMT.root\", 4, \"pf\", 15, $DHFile, true)"

mv Result* data_ZMT/
mv Summary* data_ZMT/
mv FitPlot* data_ZMT/
mv FitResult* data_ZMT/
mv FinalPlot* data_ZMT/


DHFile="\"Samples/zjets-sara-nocut.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/zjets-sara.root\", 4, \"pf\", 30, $DHFile, false)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/zjets-sara.root\", 4, \"pf\", 15, $DHFile, false)"

DHFile="\"Samples/zjets-sara-mtcut.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/zjets-sara.root\", 4, \"pf\", 30, $DHFile, true)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/zjets-sara.root\", 4, \"pf\", 15, $DHFile, true)"

mv Result* zjets-sara/
mv Summary* zjets-sara/
mv FitPlot* zjets-sara/
mv FitResult* zjets-sara/
mv FinalPlot* zjets-sara/




