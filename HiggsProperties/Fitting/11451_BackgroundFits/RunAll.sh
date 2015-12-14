#!/bin/sh

for SignalCount in `seq 1 100`
do
   for BackgroundCount in `seq 1 50`
   do
      time ./a.out $SignalCount $BackgroundCount
   done
done

mv Likelihoods_* Result/
hadd -f AllResults.root Result/*root





