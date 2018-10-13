#!/bin/bash

for i in `ls -l Result/*root | awk '{if($5 < 20000) print $9}'`
do
   ID=`echo $i | tr '_.' ' ' | awk '{print $2,$3}' | tr ' ' '_'`
   echo $ID

   cat TemplateResubmit.sh | sed "s#__WORKDIR__#$PWD#g" | sed "s/__ID__/$ID/g" | bsub -J RerunHLT -M 4000000
done



