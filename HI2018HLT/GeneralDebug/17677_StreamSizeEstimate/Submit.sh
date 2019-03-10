#!/bin/bash

mkdir -p Result/

for t in MinBias # DiJet80
do
   Files=`cat ${t}List.txt | sed "s/^/'/" | sed "s/$/',/" | tr '\n' ' '`

   ID=0
   for i in `echo $Files | Reformat 1 | tr ' ' '@'`
   do
      ID=`echo $ID | AddConst 1`
      echo $t $ID $i

      cat Template.sh \
         | sed "s#__SAMPLETYPE__#$t#" \
         | sed "s#__WORKDIR__#$PWD#g" \
         | sed "s#__INPUT__#$i#" \
         | sed "s#__ID__#$ID#" | bsub -J RunHLT -M 4000000
   done
done


