for i in `cat DoubleIndex`
do
   echo $i
   time (./a.out `echo $i | sed "s/_/ /g"` > Expression_$i)
done


