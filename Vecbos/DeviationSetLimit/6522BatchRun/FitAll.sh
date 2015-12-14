#!/bin/sh

DataFile=Samples/DataAllTrimmedStage2.root

for j in 35 40
do
   for i in `seq 5 10`
   do
      root -l -b -q "SimultaneousFit.C+(\"$DataFile\", 4, \"PF\", $j, \"Samples/DataAll.dh\", $i)"
      mv ResultPlots* Result/
   done
done

