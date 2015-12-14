mkdir -p CollectedResults

for i in A J
do
   for j in 50 100 200 400 600 1000 2000 4000 7000 10000
   do
      for k in BothS EMS EES
      do
         hadd -f CollectedResults/Result${k}_SM_${i}_${j}.root Result/FitResult_Job${k}_SM_*_${i}_${j}.root
         # hadd -f CollectedResults/Result${k}_A1ZZ_${i}_${j}.root Result/FitResult_Job${k}_A1ZZ_*_${i}_${j}.root
      done
   done
done

