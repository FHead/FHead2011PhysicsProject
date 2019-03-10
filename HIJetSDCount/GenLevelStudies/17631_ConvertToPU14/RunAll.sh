for i in `ls ../../Samples/Jewel`
do
   for j in `ls ../../Samples/Jewel/$i/*root`
   do
      echo $j
      ./a.out $j `basename ${j/.root/.pu14}`
   done
done
