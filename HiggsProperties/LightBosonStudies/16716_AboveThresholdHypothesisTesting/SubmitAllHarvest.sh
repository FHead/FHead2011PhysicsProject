for Model1 in A1UU A1UZ A2UA A2UU A2UZ A3UU
do
   for Model2 in A1UU A1UZ A2UA A2UU A2UZ A3UU
   do
      if [[ "$Model1" > "$Model2" ]]
      then
         cat HarvestSubmit.template | \
            sed "s/__MODEL1__/$Model1/g" | \
            sed "s/__MODEL2__/$Model2/g" | \
            bsub -J Harvesting -q 1nw
      fi
   done
done
