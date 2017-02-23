for i in `seq 1 500`
do
   j=`printf "%06d" $i`
   echo "./Run 18.4 0 $i > Result_$j.txt"
   ./Run 18.4 0 $i > Result_$j.txt
done
