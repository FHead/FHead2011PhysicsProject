DHFile="\"Samples/DataAll.dh\""

root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", 5, \"pf\", 15, $DHFile)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", 4, \"pf\", 30, $DHFile)"

