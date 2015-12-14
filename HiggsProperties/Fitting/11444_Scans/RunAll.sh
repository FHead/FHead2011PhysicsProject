for i in `seq 1 100` `seq 110 10 500` `seq 550 50 1000`
do
   ./a.out $i
done

mkdir -p Individual/
mv Likelihoods_[0-9]* Individual/
hadd Likelihoods_All.root Individual/Likelihoods_*





