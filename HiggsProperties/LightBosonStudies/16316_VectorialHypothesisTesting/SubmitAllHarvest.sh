for Model1 in A1UU A1UUpA2UURI A1UUpA3UU A1UZ A1UZpA2UA A2UA A2UApA2UZ A2UU A2UZ A3UU
do
   for Model2 in A1UU A1UUpA2UURI A1UUpA3UU A1UZ A1UZpA2UA A2UA A2UApA2UZ A2UU A2UZ A3UU
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
