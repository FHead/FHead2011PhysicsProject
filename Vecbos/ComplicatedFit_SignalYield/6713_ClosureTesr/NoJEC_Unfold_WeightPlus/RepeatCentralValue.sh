#!/bin/sh

PF30Smear="\"Samples/Z2SmearingMatrix\""

Data="\"Samples/data_w30P.root\""
DHFile="\"Samples/NoJEC_Unfold_WeightPlus.dh\""
SecondDHFile="\"CollectResult.dh\""

for i in `seq 1 50`
do
   root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear, $SecondDHFile)"
done































