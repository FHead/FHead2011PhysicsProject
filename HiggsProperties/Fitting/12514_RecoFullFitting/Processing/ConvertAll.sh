for i in H*gif
do
   echo $i
   convert $i -transparent white Temp_$i &
   sleep 0.05
done
