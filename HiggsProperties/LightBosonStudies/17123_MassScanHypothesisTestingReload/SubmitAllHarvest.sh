for Mass in 18p4 18p8 18p9 18p92 18p94 19p0 19p3
do
   for Model1 in A1UU A1UZ A2UA A2UU A2UZ A3UU A3UA A3UZ
   do
      for Model2 in A1UU A1UZ A2UA A2UU A2UZ A3UU A3UA A3UZ
      do
         if [[ "$Model1" > "$Model2" ]]
         then
            cat HarvestSubmit.template | \
               sed "s/__MODEL1__/$Model1/g" | \
               sed "s/__MODEL2__/$Model2/g" | \
               sed "s/__MASS__/$Mass/g" | \
               bsub -J Harvesting -q 1nd
         fi
      done
   done
done
