mkdir -p CollectedResults

for i in A H I J
do
   for j in 50 100 200 400 600 1000 2000 4000 7000 10000
   do
      for k in BothS # EMS EES
      do
         hadd -f CollectedResults/Result${k}_Point0_${i}_${j}.root Result/FitResult_Job${k}_Point0_*_${i}_${j}.root
      done
   done
done

