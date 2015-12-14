mkdir -p CollectedResults

# for i in A B C D E F G H I J
for i in A 
do
   for j in 50 100 200 400 600 1000 2000 4000 7000 10000
   do
      hadd -f CollectedResults/Result_SM_${i}_${j}.root Result/FitResult_JobEM_SM_*_${i}_${j}.root
      hadd -f CollectedResults/Result_A1ZZ_${i}_${j}.root Result/FitResult_JobEM_A1ZZ_*_${i}_${j}.root
   done
done

