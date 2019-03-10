#!/bin/bash

SampleName=$1
SampleTagBase=$2
SampleFileBase=$3

for ID1 in `seq 1 10`
do
   for ID2 in `seq 0 14`
   do
      Tag=${ID1}_${ID2}

      SampleFile=${SampleFileBase}_${Tag}.pu14
      OutputTag=${SampleTagBase}_${Tag}

      cat RunJob.sh \
         | sed "s#__WORKDIR__#$PWD#g" \
         | sed "s#__SAMPLENAME__#$SampleName#g" \
         | sed "s#__SAMPLE__#$SampleFile#g" \
         | sed "s#__OUTPUTTAG__#$OutputTag#g" | bsub -J Run$SampleTagBase -q 8nh
   done
done



