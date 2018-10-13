#!/bin/bash

Files=
for i in `ls Samples/*root`
do
   Files=`echo $Files \'file:$i\',`
done

ID=0
for i in `echo $Files | Reformat 2 | tr ' ' '@'`
do
   ID=`echo $ID | AddConst 1`
   echo $ID $i

   cat Template.sh \
      | sed "s#__INPUT__#$i#" \
      | sed "s#__ID__#$ID#" | bsub -J RunHLT -M 4000000
done



