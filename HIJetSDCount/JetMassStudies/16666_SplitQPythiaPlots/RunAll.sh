#!/bin/sh

# Directory=16543Samples
# Directory=16552MasslessSamples
# Directory=16574LargeJewelSamplesMerged
Directory=16666Samples

CompileRootMacro MakeJetMassPlots.cpp

for i in qhat1 vac
do
   for j in SB
   do
      for k in N
      do
         time ./a.out $Directory/Result_QPythia_${j}_${i}.root Plots_${i}_${j}_${k} ${k}
      done
   done
done

exit

CompileRootMacro CollectJetMassPlots.cpp

./a.out

CompileRootMacro PickPlots.cpp

./a.out
