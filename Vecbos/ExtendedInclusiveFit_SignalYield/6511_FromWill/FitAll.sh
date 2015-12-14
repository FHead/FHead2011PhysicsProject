#!/bin/sh

DHFile="\"Samples/data_w30_weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile, true)"

# DHFile="\"Samples/data_w30_unweighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile, false)"

# DHFile="\"Samples/data_w15_weighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, $DHFile, true)"

# DHFile="\"Samples/data_w15_unweighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, $DHFile, false)"

mv Result* Normal/
mv Summary* Normal/
mv FitPlot* Normal/
mv FitResult* Normal/
mv FinalPlot* Normal/


exit

DHFile="\"Samples/data_w30P_weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30P.root\", 4, \"pf\", 30, $DHFile, true)"

DHFile="\"Samples/data_w30P_unweighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30P.root\", 4, \"pf\", 30, $DHFile, false)"

# DHFile="\"Samples/data_w15P_weighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15P.root\", 4, \"pf\", 15, $DHFile, true)"

# DHFile="\"Samples/data_w15P_unweighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15P.root\", 4, \"pf\", 15, $DHFile, false)"

mv Result* Plus/
mv Summary* Plus/
mv FitPlot* Plus/
mv FitResult* Plus/
mv FinalPlot* Plus/


DHFile="\"Samples/data_w30M_weighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30M.root\", 4, \"pf\", 30, $DHFile, true)"

DHFile="\"Samples/data_w30M_unweighted.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30M.root\", 4, \"pf\", 30, $DHFile, false)"

# DHFile="\"Samples/data_w15M_weighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15M.root\", 4, \"pf\", 15, $DHFile, true)"

# DHFile="\"Samples/data_w15M_unweighted.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15M.root\", 4, \"pf\", 15, $DHFile, false)"

mv Result* Minus/
mv Summary* Minus/
mv FitPlot* Minus/
mv FitResult* Minus/
mv FinalPlot* Minus/


