#!/bin/sh

source Setup_FileLocation.sh

Input=$WithPUFiles
Output=$Step3Output

Count=0
for i in `ls $Input | ./Columnize 20 | tr ' ' ':'`
do
   echo $i
   File=`echo $i | tr ':' ' '`
   cat Step3ApplyL1.sh \
      | sed "s#__FILE__#$File#g" \
      | sed "s#__ID__#$Count#g" \
      | sed "s#__WORKDIR__#`pwd`#g" \
      | sed "s#__OUTPUT__#$Output#" \
      | bsub -J ApplyL1
   Count=`echo $Count | AddConst 1`
done

