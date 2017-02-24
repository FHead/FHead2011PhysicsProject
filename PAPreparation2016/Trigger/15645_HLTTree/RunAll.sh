for i in `ls Data/`
do
   echo $i
   ./a.out Data/$i Output/$i
done
