for ID in `seq 1 6`
do
   for Cut in P F
   do
      for Model in A1UU
      do
         cat BatchSubmit.template | \
            sed "s/__MODEL__/$Model/g" | \
            sed "s/__CUT__/$Cut/g" | \
            sed "s/__ID__/$ID/g" | \
            bsub -J Spin0Fits -q 1nw -M 3000000
      done
   done
done
