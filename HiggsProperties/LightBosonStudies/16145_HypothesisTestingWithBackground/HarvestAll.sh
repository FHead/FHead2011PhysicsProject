#!/bin/sh

# ./a.out Model1 Model2 Cut Scenario File1 File2

for Cut in F P
do
   for Scenario in `seq 0 9`
   do
      for Model1 in A1UU A2UA A2UU A2UZ A3UU A1UURIpA1UZRI A1UUpA3UU A1UURpA1UZR
      do
         for Model2 in A1UU A2UA A2UU A2UZ A3UU A1UURIpA1UZRI A1UUpA3UU A1UURpA1UZR
         do
            if [[ "$Model1" > "$Model2" ]]
            then
               ./a.out $Model1 $Model2 $Cut $Scenario \
                  ExportedLikelihood/LikelihoodFixed_${Model1}_${Cut}_1_Scenario$Scenario \
                  ExportedLikelihood/LikelihoodFixed_${Model2}_${Cut}_1_Scenario$Scenario
            fi
         done
      done
   done
done




