for Mass in 18p4 18p8 18p92 18p94 18p9 19p0 19p3
do
   echo START RUNNING MASS = $Mass
   for ID in `seq 1 50`
   do
      for Cut in P
      do
         for Model in A1UU A1UZ A2UA A2UU A2UZ A3UU A3UZ A3UA
         do
            cat BatchSubmit.template | \
               sed "s/__MODEL__/$Model/g" | \
               sed "s/__CUT__/$Cut/g" | \
               sed "s/__ID__/$ID/g" | \
               sed "s/__MASS__/$Mass/g" | \
               sed "s/__DHFILE__/Normalization_${Mass/p/.}.dh/g" | \
               bsub -J BetterHypothesisTesting -q 1nd -M 3000000
         done
      done
   done
done
