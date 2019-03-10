#!/bin/sh

SampleLocation=16552MasslessSamples
SampleLocation=16543Samples
SampleLocation=16574LargeJewelSamplesMerged

CompileRootMacro MakeJetRAAPlots.cpp

for i in On Off
do
   for j in S SB
   do
      for k in Y N
      do
         ./a.out $SampleLocation/Result_Recoil${i}_${j}.root Plots_${i}_${j}_${k} ${k}
      done
   done
done

for j in S SB
do
   for k in Y N
   do
      ./a.out $SampleLocation/Result_Vac_${j}.root Plots_Vac_${j}_${k} ${k}
   done
done

# for i in Q1 Q2 Q4 QB1 QB2 QB4 Vac VacB
# do
#    ./a.out $SampleLocation/Result_QPythia_${i}.root Plots_QPythia_${i}_N N
# done

CompileRootMacro CollectRAAPlots.cpp

./a.out
