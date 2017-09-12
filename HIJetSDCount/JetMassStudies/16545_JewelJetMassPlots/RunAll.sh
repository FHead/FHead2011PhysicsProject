#!/bin/sh

CompileRootMacro MakeJetMassPlots.cpp

# for i in On Off
# do
#    for j in S SB P
#    do
#       for k in Y N
#       do
#          ./a.out 16543Samples/Result_Recoil${i}_${j}.root Plots_${i}_${j}_${k} ${k}
#       done
#    done
# done

# for i in Vac
# do
#    for j in S SB
#    do
#       for k in Y N
#       do
#          ./a.out 16543Samples/Result_${i}_${j}.root Plots_${i}_${j}_${k} ${k}
#       done
#    done
# done

for i in QPythia
do
   for j in S SB P PB
   do
      ./a.out 16543Samples/Result_${i}_${j}.root Plots_${i}_${j}_N N
   done
done

CompileRootMacro CollectJetMassPlots.cpp

./a.out

