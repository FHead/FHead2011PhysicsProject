for iS in `seq 10 5 50`
do
   for iB in `seq 5 5 25`
   do
      ./a.out $iS $iB 1125
      mv Likelihoods_${iS}_${iB}.* 1125/
      
      ./a.out $iS $iB 8125
      mv Likelihoods_${iS}_${iB}.* 8125/
   done
done

hadd -f Likelihoods_All_1125.root 1125/*root
hadd -f Likelihoods_All_8125.root 8125/*root






