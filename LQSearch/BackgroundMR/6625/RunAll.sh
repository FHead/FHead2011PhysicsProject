for i in `ls Samples/ | grep root$ | sed "s/.root//g"`
do
   echo ./CheckMR $i
   # time ./CheckMR $i
done
