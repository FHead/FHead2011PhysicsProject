mkdir -p CollectedResults

for i in A J # A H I J
do
   for j in 50 100 200 400 600 1000 2000 4000 7000 10000
   do
      for k in BothS Both # EMS EES EM EE
      do
         # hadd -f -k CollectedResults/Result${k}_Point0_${i}_${j}.root Result/FitResult_Job${k}_Point0_*_${i}_${j}.root
         # hadd -f -k CollectedResults/Result${k}_PointA_${i}_${j}.root Result/FitResult_Job${k}_PointA_*_${i}_${j}.root
         hadd -f -k CollectedResults/Result${k}_PointAPrime_${i}_${j}.root Result/FitResult_Job${k}_PointAPrime_*_${i}_${j}.root
         # hadd -f -k CollectedResults/Result${k}_PointD_${i}_${j}.root Result/FitResult_Job${k}_PointD_*_${i}_${j}.root
         # hadd -f -k CollectedResults/Result${k}_PointH5_${i}_${j}.root Result/FitResult_Job${k}_PointH5_*_${i}_${j}.root
      done
   done
done

