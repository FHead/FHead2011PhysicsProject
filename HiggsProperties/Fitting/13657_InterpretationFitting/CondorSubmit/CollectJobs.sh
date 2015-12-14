mkdir -p CollectedResults

for i in A H I J
do
   for j in 50 100 200 400 600 1000 2000 4000 7000 10000
   do
      for k in BothS EMS EES
      do
         echo
         hadd -f CollectedResults/Result${k}_PointA_${i}_${j}.root Result/FitResult_Job${k}_PointA_*_${i}_${j}.root
         # hadd -f CollectedResults/Result${k}_PointB_${i}_${j}.root Result/FitResult_Job${k}_PointB_*_${i}_${j}.root
      done
         
      hadd -f CollectedResults/ResultBoth_PointA_${i}_${j}.root Result/FitResult_JobBoth_PointA_*_${i}_${j}.root
      hadd -f CollectedResults/ResultBothF_PointA_${i}_${j}.root Result/FitResult_JobBothF_PointA_*_${i}_${j}.root
   done
done

