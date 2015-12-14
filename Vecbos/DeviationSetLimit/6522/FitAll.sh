#!/bin/sh

DataFile=Samples/DataAllTrimmedStage2.root

for i in 44.25 44.5
do
   root -l -b -q "SimultaneousFit.C+(\"$DataFile\", 4, \"PF\", 30, \"Samples/DataAll.dh\", $i)"
done

