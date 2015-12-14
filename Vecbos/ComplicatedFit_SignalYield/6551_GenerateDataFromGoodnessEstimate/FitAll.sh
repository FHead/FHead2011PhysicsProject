#!/bin/sh

DHFile="\"Samples/data_w15_unweighted.dh\""
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, $DHFile, false)"

# DHFile="\"Samples/data_w30_unweighted.dh\""
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile, false)"






