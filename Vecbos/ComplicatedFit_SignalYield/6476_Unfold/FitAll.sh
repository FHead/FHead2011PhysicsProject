#!/bin/sh

# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, \"Samples/data_w15_weighted.dh\", true, \"Samples/PF15SmearingMatrix\")"
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, \"Samples/data_w15_unweighted.dh\", false, \"Samples/PF15SmearingMatrix\")"

# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, \"Samples/data_w30_weighted.dh\", true, \"Samples/PF30SmearingMatrix\")"
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, \"Samples/data_w30_unweighted.dh\", false, \"Samples/PF30SmearingMatrix\")"



