#!/bin/sh

DHFile="\"Samples/datau_JECP.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data-w30mt_JECP.root\", 4, \"pf\", 30, $DHFile, false)"
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data-w15mt_JECP.root\", 4, \"pf\", 15, $DHFile, false)"

DHFile="\"Samples/dataw_JECP.dh\""
# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data-w30mt_JECP.root\", 4, \"pf\", 30, $DHFile, true)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data-w15mt_JECP.root\", 4, \"pf\", 15, $DHFile, true)"

mv Result* Plus/
mv Summary* Plus/
mv FitPlot* Plus/
mv FitResult* Plus/
mv FinalPlot* Plus/


exit

DHFile="\"Samples/datau_JECM.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data-w30mt_JECM.root\", 4, \"pf\", 30, $DHFile, false)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data-w15mt_JECM.root\", 4, \"pf\", 15, $DHFile, false)"

DHFile="\"Samples/dataw_JECM.dh\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data-w30mt_JECM.root\", 4, \"pf\", 30, $DHFile, true)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data-w15mt_JECM.root\", 4, \"pf\", 15, $DHFile, true)"

mv Result* Minus/
mv Summary* Minus/
mv FitPlot* Minus/
mv FitResult* Minus/
mv FinalPlot* Minus/


