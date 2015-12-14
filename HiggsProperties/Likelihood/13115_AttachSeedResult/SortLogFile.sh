#!/bin/sh

mkdir -p Temp

for i in `ls BatchResult/ | tr -d '\\'`
do
   for j in Central BCentral
   do
      cat BatchResult/$i/*txt \
         | grep " $j " \
         | grep ".root" \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done


