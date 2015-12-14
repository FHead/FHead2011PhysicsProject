for i in *out
do
   tail -n+20 $i | grep ^[1-9] > ../Processing/Log/$i
done
