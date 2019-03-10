#!/bin/sh

SampleLocation=16552MasslessSamples
SampleLocation=16543Samples

CompileRootMacro MakeJetRAAPlots.cpp

for i in On Off
do
   for j in S SB P
   do
      for k in Y N
      do
         ./a.out $SampleLocation/Result_Recoil${i}_${j}.root Plots_${i}_${j}_${k} ${k}
      done
   done
done

for i in S SB P PB Q QB
do
   ./a.out $SampleLocation/Result_QPythia_${i}.root Plots_QPythia_${i}_N N
done

CompileRootMacro CollectRAAPlots.cpp

./a.out
