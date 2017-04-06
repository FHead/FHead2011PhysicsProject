#!/bin/sh

for EventCount in 100_100_100_100
do
   for ID in `seq 1 10`
   do
      for Cut in P F
      do
         for Model in A1UU A2UU A2UA A2UZ A1UUpA3UU
         do
            SEM=`echo $EventCount | cut --delim='_' --field=1`
            BEM=`echo $EventCount | cut --delim='_' --field=2`
            SEE=`echo $EventCount | cut --delim='_' --field=3`
            BEE=`echo $EventCount | cut --delim='_' --field=4`

            cat BatchSubmit.template | \
               sed "s/__MODEL__/$Model/g" | \
               sed "s/__CUT__/$Cut/g" | \
               sed "s/__ID__/$ID/g" | \
               sed "s/__SEM__/$SEM/g" | \
               sed "s/__SEE__/$SEE/g" | \
               sed "s/__BEM__/$BEM/g" | \
               sed "s/__BEE__/$BEE/g" | \
               bsub -J BetterHypothesisTesting -q 8nh

            exit
         done
      done
   done
done
