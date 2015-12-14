#!/bin/sh

mkdir -p Temp

for i in EventB.root Madgraph2e2mu_100_160_part1.root Madgraph2e2mu_100_160_part2.root \
   Madgraph2e2mu_100_160_part3.root Madgraph2e2mu_100_160_part4.root \
   Madgraph2e2mu_100_160_part5.root Madgraph2e2mu_100_160_part6.root
do
   echo $i
   for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
      BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   # for j in BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   do
      cat BatchResult/${i}_* | grep "$i " | grep " $j " \
         | grep -v nan \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done


