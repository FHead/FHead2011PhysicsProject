for ID in `seq 1 30`
do
   for Cut in P F T
   do
      for Model in A1UU A2UU A2UZ A3UU A2UA A1UZ
      do
         cat BatchSubmit.template | \
            sed "s/__MODEL__/$Model/g" | \
            sed "s/__CUT__/$Cut/g" | \
            sed "s/__ID__/$ID/g" | \
            bsub -J Spin0Fits -q 1nd -M 3000000
      done
   done
done
