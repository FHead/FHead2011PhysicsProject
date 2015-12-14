#!/bin/sh

mkdir -p Temp

for i in `ls CleanTrees | grep ^E | grep _21`
do
   echo $i
   for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
      BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   # for j in BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   do
      cat BatchResult/*_${i} | grep "$i " | grep " $j " \
         | grep -v nan \
         | cut -d ' ' -f 3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done


