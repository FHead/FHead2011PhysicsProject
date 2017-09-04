#!/bin/sh

for i in On Off
do
   for j in S SB P
   do
      for k in Y N
      do
         ./a.out 16541Samples/Result_Recoil${i}_${j}.root Plots_${i}_${j}_${k} ${k}
      done
   done
done


