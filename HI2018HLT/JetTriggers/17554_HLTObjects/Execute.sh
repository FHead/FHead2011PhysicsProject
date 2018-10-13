#!/bin/bash

Files=
for i in `ls Samples/*root`
do
   Files=`echo $Files \"file:$i\",`
done

ID=0
for i in `echo $Files | Reformat 20 | tr ' ' ';'`
do
   j=`echo $i | tr ';' ' ' | sed "s/,$//"`
   ID=`echo $ID | AddConst 1`
   echo $ID $j

   sed "s#__FILE__#$j#" < ExportedMenuV36.py \
      | sed "s#__ID__#$ID#" > FinalMenu_${ID}.py
done

for i in `seq 1 25`
do
   echo Running $i
   cmsRun FinalMenu_$i.py >& /tmp/chenyi/Log_$i
   bzip2 /tmp/chenyi/Log_$i
   mv /tmp/chenyi/Log_$i.bz2 .
done


