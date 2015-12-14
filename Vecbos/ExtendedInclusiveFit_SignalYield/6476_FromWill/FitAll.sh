#!/bin/sh

# DHFile="\"Samples/data_w30_weighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile, true)"

# DHFile="\"Samples/data_w30_unweighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile, false)"

DHFile="\"Samples/data_w15_weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, $DHFile, true)"

DHFile="\"Samples/data_w15_unweighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, $DHFile, false)"



