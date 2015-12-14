for i in *root
do
   ./a.out $i ${i/.root/}
done
