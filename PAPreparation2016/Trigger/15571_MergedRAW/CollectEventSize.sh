for i in `cat TriggerList.txt`
do
   echo "$i `edmEventSize -v Output/${i}[0-9]_Merged.root | grep FEDRawDataCollection | awk '{print $2,$3}'` `edmEventSize -v Output/${i}[0-9]_Merged.root | grep ^File | awk '{print $4}'`"
done | tee Result.txt
