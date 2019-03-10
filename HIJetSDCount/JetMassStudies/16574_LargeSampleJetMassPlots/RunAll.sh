#!/bin/sh

# Directory=16543Samples
# Directory=16552MasslessSamples
Directory=16574LargeJewelSamplesMerged

CompileRootMacro MakeJetMassPlots.cpp

for i in On Off
do
   for j in S SB
   do
      for k in Y N
      do
         time ./a.out $Directory/Result_Recoil${i}_${j}.root Plots_${i}_${j}_${k} ${k}
      done
   done
done

# for i in Vac
# do
#    for j in S SB
#    do
#       for k in Y N
#       do
#          time ./a.out $Directory/Result_${i}_${j}.root Plots_${i}_${j}_${k} ${k}
#       done
#    done
# done

# for i in QPythia
# do
#    for j in Q1 Q2 Q4 QB1 QB2 QB4 Vac VacB
#    do
#       time ./a.out $Directory/Result_${i}_${j}.root Plots_${i}_${j}_N N
#    done
# done

CompileRootMacro CollectJetMassPlots.cpp

./a.out

CompileRootMacro PickPlots.cpp

./a.out
