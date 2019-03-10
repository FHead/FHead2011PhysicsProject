#!/bin/sh

JOB=0
for i in `cat FileList.txt`
do
   JOB=`echo $JOB | AddConst 1`
   cat RunJob.sh \
      | sed "s#__FILE__#$i#g" \
      | sed "s#__HERE__#$PWD#g" \
      | bsub -q 8nh -J HLTRate_$JOB
done
