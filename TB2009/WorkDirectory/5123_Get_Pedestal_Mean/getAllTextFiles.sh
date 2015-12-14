for i in `cat $1`
do
   root -l -q "GetPedestalMean.C+(\"AdcDistribution_$i.root\", \"PedestalMean_$i.txt\")" | grep Processing
done

