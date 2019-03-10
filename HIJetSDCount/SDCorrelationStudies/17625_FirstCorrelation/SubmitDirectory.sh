#!/bin/bash

SampleName=$1
SampleTagBase=$2
SampleFileBase=$3

for File in `ls InstallDir/Samples/${SampleName}`
do
   Tag=${File/.pu14}
   SampleFile=${File}
   OutputTag=${SampleTagBase}_${Tag}

   cat RunJobDirectory.sh \
      | sed "s#__WORKDIR__#$PWD#g" \
      | sed "s#__SAMPLENAME__#$SampleName#g" \
      | sed "s#__SAMPLE__#$SampleFile#g" \
      | sed "s#__OUTPUTTAG__#$OutputTag#g" | bsub -J Run$SampleTagBase -q 2nd
done



