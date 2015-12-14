#!/bin/sh

for i in AlphaL AlphaR SigmaL SigmaR
do
   root -l -b -q "MakeSummaryPlots.C+(\"SummaryTree/Output$i.root\", \"$i\")"
done


