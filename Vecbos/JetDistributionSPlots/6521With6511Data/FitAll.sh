DHFile="\"Samples/data_w30_weighted.dh\""

# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", 5, \"pf\", 15, $DHFile)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile)"



