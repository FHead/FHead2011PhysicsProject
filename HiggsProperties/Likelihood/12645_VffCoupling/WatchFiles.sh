for j in `seq 1 10000`
do
   for i in `du --max-depth=1 -h | grep 1[56789][0-9]M | awk '{print $2}'`
   do
      mv $i/*root ../BatchResult/
   done
   echo Start sleeping
   sleep 10
   echo Waking up
done


