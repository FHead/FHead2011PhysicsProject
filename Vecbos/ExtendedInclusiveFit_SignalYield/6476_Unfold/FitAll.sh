#!/bin/sh

DHFile="\"Samples/data_w30_weighted.dh\""
SmearingFile="\"Samples/PF30SmearingMatrix\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile, true, $SmearingFile)"

DHFile="\"Samples/data_w30_unweighted.dh\""
SmearingFile="\"Samples/PF30SmearingMatrix\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile, false, $SmearingFile)"

DHFile="\"Samples/data_w15_weighted.dh\""
SmearingFile="\"Samples/PF15SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, $DHFile, true, $SmearingFile)"

DHFile="\"Samples/data_w15_unweighted.dh\""
SmearingFile="\"Samples/PF15SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, $DHFile, false, $SmearingFile)"



