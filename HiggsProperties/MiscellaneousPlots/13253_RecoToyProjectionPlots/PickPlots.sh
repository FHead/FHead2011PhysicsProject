#!/bin/sh

mkdir -p PickedPlots

for i in `seq 0 7`
do
   for j in png C pdf eps
   do
      cp ComparisonPlots${i}.${j} PickedPlots/MultiDimensionalValidation-Likelihood-SignalSM_${i}.${j}
      cp ComparisonPlots${i}_FA2.${j} PickedPlots/MultiDimensionalValidation-Likelihood-SignalFA2_${i}.${j}
      cp ComparisonPlots${i}_FA3.${j} PickedPlots/MultiDimensionalValidation-Likelihood-SignalFA3_${i}.${j}
   done
done




