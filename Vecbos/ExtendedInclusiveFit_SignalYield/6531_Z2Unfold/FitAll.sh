#!/bin/sh

DHFile="\"Samples/data_w30_weighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF30SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile, true, $SmearingFile)"

DHFile="\"Samples/data_w30_unweighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF30SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, $DHFile, false, $SmearingFile)"

DHFile="\"Samples/data_w15_weighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF15SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, $DHFile, true, $SmearingFile)"

DHFile="\"Samples/data_w15_unweighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF15SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, $DHFile, false, $SmearingFile)"

mv FinalPlot* Normal/
mv Result* Normal/
mv FitResult* Normal/
mv FitPlot* Normal/
mv Summary* Normal/





DHFile="\"Samples/data_w30P_weighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF30SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30P.root\", 4, \"pf\", 30, $DHFile, true, $SmearingFile)"

DHFile="\"Samples/data_w30P_unweighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF30SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30P.root\", 4, \"pf\", 30, $DHFile, false, $SmearingFile)"

DHFile="\"Samples/data_w15P_weighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF15SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15P.root\", 4, \"pf\", 15, $DHFile, true, $SmearingFile)"

DHFile="\"Samples/data_w15P_unweighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF15SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15P.root\", 4, \"pf\", 15, $DHFile, false, $SmearingFile)"

mv FinalPlot* Plus/
mv Result* Plus/
mv FitResult* Plus/
mv FitPlot* Plus/
mv Summary* Plus/





DHFile="\"Samples/data_w30M_weighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF30SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30M.root\", 4, \"pf\", 30, $DHFile, true, $SmearingFile)"

DHFile="\"Samples/data_w30M_unweighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF30SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w30M.root\", 4, \"pf\", 30, $DHFile, false, $SmearingFile)"

DHFile="\"Samples/data_w15M_weighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF15SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15M.root\", 4, \"pf\", 15, $DHFile, true, $SmearingFile)"

DHFile="\"Samples/data_w15M_unweighted_Z2.dh\""
SmearingFile="\"Samples/Z2PF15SmearingMatrix\""
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/data_w15M.root\", 4, \"pf\", 15, $DHFile, false, $SmearingFile)"

mv FinalPlot* Minus/
mv Result* Minus/
mv FitResult* Minus/
mv FitPlot* Minus/
mv Summary* Minus/





