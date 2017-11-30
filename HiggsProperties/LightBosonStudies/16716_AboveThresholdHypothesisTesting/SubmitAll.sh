for ID in `seq 1 30`
do
   for Cut in P F
   do
      for Model in A1UU A1UZ A2UA A2UU A2UZ A3UU
      do
         cat BatchSubmit.template | \
            sed "s/__MODEL__/$Model/g" | \
            sed "s/__CUT__/$Cut/g" | \
            sed "s/__ID__/$ID/g" | \
            bsub -J BetterHypothesisTesting -q 1nw -M 3000000
      done
   done
done
