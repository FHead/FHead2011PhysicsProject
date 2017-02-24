mkdir -p Calculated

for i in `seq 31 90`
do
   for j in A J
   do
      for k in JobBoth JobBothS
      do
         for m in 25 50 100 200 400 800 1600 3200 6400 12800 25600
         do
            for l in 5plet # SMVV 5plet
            do
               FileName=${k}_${l}_ggPDF_${j}_${m}_${i}.out
               echo Processing $FileName
               ./Calculate < Log/$FileName > Calculated/$FileName
            done
         done
      done
   done
done


