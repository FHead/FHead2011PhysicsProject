mkdir -p CollectedResults

for i in A J # A H I J
do
   for j in 25 50 100 200 400 800 1600 3200 6400 12800 25600
   do
      for k in Both BothS
      do
         echo
         hadd -f -k CollectedResults/Job${k}_SMVV_ggPDF_${i}_${j}.root Result/FitResult_Job${k}_SMVV_ggPDF_${i}_${j}_*
         hadd -f -k CollectedResults/Job${k}_5plet_ggPDF_${i}_${j}.root Result/FitResult_Job${k}_5plet_ggPDF_${i}_${j}_*
      done
   done
done

mkdir -p HyperCollectedResults

for i in A J
do
   for k in Both BothS
   do
      hadd -f -k HyperCollectedResults/Job${k}_SMVV_ggPDF_${i}.root CollectedResults/Job${k}_SMVV_ggPDF_${i}_*.root
      hadd -f -k HyperCollectedResults/Job${k}_5plet_ggPDF_${i}.root CollectedResults/Job${k}_5plet_ggPDF_${i}_*.root
   done
done

