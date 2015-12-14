#!/bin/sh

root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15.root\", 5, \"pf\", 15, \"Samples/data_w15_weighted.dh\", true)"
root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15.root\", 5, \"pf\", 15, \"Samples/data_w15_unweighted.dh\", false)"

# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, \"Samples/data_w30_weighted.dh\", true)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, \"Samples/data_w30_unweighted.dh\", false)"



