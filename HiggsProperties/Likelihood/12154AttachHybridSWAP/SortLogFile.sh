#!/bin/sh

mkdir -p Temp

for i in EventB.root EventXi[12]*root Madgraph*part1.root
do
   echo $i
   # for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
   #    BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   for j in BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   do
      cat BatchResult/${i}_* | grep "^$i " | grep " $j " \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done


