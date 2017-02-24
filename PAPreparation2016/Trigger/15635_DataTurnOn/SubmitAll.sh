Run=285480
Type=Streamer

for Type in Data #Data Streamer
do
   for Run in 285750 #285759 # 285480 #285216 285090 285244 285368 285369 285371 285480 285505 285517
   do
      for i in `ls ${Type}Base/${Run:0:3}/${Run:3:3}`
      do
         Index=`echo $i | sed "s/HiForest_//" | sed "s/.root//"`
         cat RunBatch.sh \
            | sed "s/__TYPE__/$Type/g" \
            | sed "s/__RUN__/$Run/g" \
            | sed "s/__INPUT__/$i/" \
            | sed "s/__OUTPUT__/Output${Type}_${Run}_${Index}.root/" \
            | bsub -J "${Type}${Run}"
      done
   done
done


