#!/bin/sh

PF30Smear="\"Samples/PF30SmearingMatrix\""

Data="\"Samples/data_w30.root\""
DHFile="\"Samples/NoJEC_Unfold_Weighted.dh\""
SecondDHFile="\"CentralValue.dh\""

for i in `seq 1 50`
do
   root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear, $SecondDHFile)"
done































