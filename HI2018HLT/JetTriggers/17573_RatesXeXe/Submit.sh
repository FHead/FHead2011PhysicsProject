#!/bin/bash

Files=`cat FileList | tr '\n' ' '`

ID=0
for i in `echo $Files | Reformat 1 | tr ' ' '@'`
do
   ID=`echo $ID | AddConst 1`
   echo $ID $i

   cat Template.sh \
      | sed "s#__INPUT__#$i#" \
      | sed "s#__ID__#$ID#" | bsub -J RunHLTRate -M 4000000

done




