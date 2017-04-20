for ID in `seq 1 6`
do
   for Cut in P F
   do
      for Model in A1UU A1UUpA2UURI A1UUpA3UU A1UZ A1UZpA2UA A2UA A2UApA2UZ A2UU A2UZ A3UU
      do
         cat BatchSubmit.template | \
            sed "s/__MODEL__/$Model/g" | \
            sed "s/__CUT__/$Cut/g" | \
            sed "s/__ID__/$ID/g" | \
            bsub -J BetterHypothesisTesting -q 1nw -M 3000000
      done
   done
done
