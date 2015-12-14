#!/bin/sh

for HiggsMass in 100 110 120 125 130 140 160 200 300 400
do
   echo > /wntmp/yichen/All_${HiggsMass}.map7
   for i in `seq 1 12`
   do
      for j in `seq 1 15`
      do
         cat BatchResult/IndividualMap_${HiggsMass}_${i}_${j}_FixAngle.map7 >> /wntmp/yichen/All_${HiggsMass}.map7
      done
   done


   echo > /wntmp/yichen/All_${HiggsMass}_Scalar.map7
   for i in `seq 1 12`
   do
      for j in `seq 1 15`
      do
         cat BatchResult/IndividualMap_${HiggsMass}_${i}_${j}_FixAngle_Scalar.map7 >> /wntmp/yichen/All_${HiggsMass}_Scalar.map7
      done
   done


   echo > /wntmp/yichen/All_${HiggsMass}_PhaseSpace.map7
   for i in `seq 1 12`
   do
      for j in `seq 1 15`
      do
         cat BatchResult/IndividualMap_${HiggsMass}_${i}_${j}_FixAngle_PhaseSpace.map7 >> /wntmp/yichen/All_${HiggsMass}_PhaseSpace.map7
      done
   done


   echo > /wntmp/yichen/All_${HiggsMass}_PseudoScalar.map7
   for i in `seq 1 12`
   do
      for j in `seq 1 15`
      do
         cat BatchResult/IndividualMap_${HiggsMass}_${i}_${j}_FixAngle_PseudoScalar.map7 >> /wntmp/yichen/All_${HiggsMass}_PseudoScalar.map7
      done
   done
done







