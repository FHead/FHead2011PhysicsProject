for ID in `seq 1 10`
do
   for Cut in P F
   do
      for Model in A1UU A2UU A2UA A2UZ A1UUpA3UU
      do
         cat BatchSubmit.template | \
            sed "s/__MODEL__/$Model/g" | \
            sed "s/__CUT__/$Cut/g" | \
            sed "s/__ID__/$ID/g" | \
            bsub -J BetterHypothesisTesting -q 1nw
      done
   done
done
