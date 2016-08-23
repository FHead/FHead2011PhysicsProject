mkdir -p CollectedResults

for i in A J # A H I J
do
   for j in 50 100 200 400 600 1000 2000 4000 7000 10000
   do
      for k in Both EM EE
      do
         hadd -f -k CollectedResults/Job${k}_SMVV_ggPDF_${i}_${j}.root Result/FitResult_Job${k}_SMVV_ggPDF_${i}_${j}_*
         hadd -f -k CollectedResults/Job${k}_5plet_ggPDF_${i}_${j}.root Result/FitResult_Job${k}_5plet_ggPDF_${i}_${j}_*
      done
   done
done

