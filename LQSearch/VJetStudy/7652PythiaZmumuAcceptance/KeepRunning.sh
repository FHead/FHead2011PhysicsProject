for i in `seq 1 1000`
do
   j=`printf "%04d" $i`
   echo $j
   time ./RunMillion Output$j.root
done
