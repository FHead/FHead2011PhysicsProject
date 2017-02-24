#!/bin/bash

for Spin in GetXVV_15721 GetSpin1XVV_15762 GetSpin2XVV_15764
do
   FunctionFront=`echo $Spin | cut -d '_' -f 1`
   FunctionEnd=`echo $Spin | cut -d '_' -f 2`

   for Type in EEEE EEMM
   do
      Index1=0
      for i1 in Z V A
      do
         for j1 in Z V A
         do
            for k1 in 1 2 3 4
            do
               for l1 in R I
               do
                  Index2=0
                  for i2 in Z V A
                  do
                     for j2 in Z V A
                     do
                        for k2 in 1 2 3 4
                        do
                           for l2 in R I
                           do
                              A1=A${k1}${i1}${j1}${l1}
                              A2=A${k2}${i2}${j2}${l2}
                              Function=${FunctionFront}_${Type}_${A1}_${A2}_${FunctionEnd}
                              echo "   Result[$Index1][$Index2] = $Function;"

                              Index2=`echo $Index2 | AddConst 1`
                           done
                        done
                     done
                  done

                  Index1=`echo $Index1 | AddConst 1`
               done
            done
         done
      done > ${FunctionFront}_${Type}.txt
   done
done
