#!/bin/sh

for i in `seq 1 250`
do
   cat RunJob.sh \
      | sed "s/__ID__/$i/g" \
      | sed "s#__HERE__#$PWD#g" \
      | bsub -q 1nh -J HLTTurnOn_$i
done
