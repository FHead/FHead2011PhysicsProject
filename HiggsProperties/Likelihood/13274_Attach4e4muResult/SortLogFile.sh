#!/bin/sh

mkdir -p Temp

for i in `ls Source/ | grep EE`
do
   echo $i
   k=${i/.BeforeCombining/}
   k=${k/_EE/}
   echo $k
   
   for j in BCentral Central
   do
      cat BatchResult/ConvertedTree_$k*_3/Result*.txt \
         | grep "root" | grep " $j " \
         | grep -v nan \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done

for i in `ls Source/ | grep MM`
do
   echo $i
   k=${i/.BeforeCombining/}
   k=${k/_MM/}
   echo $k
   
   for j in BCentral Central
   do
      cat BatchResult/ConvertedTree_$k*_4/Result*.txt \
         | grep "root" | grep " $j " \
         | grep -v nan \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done




