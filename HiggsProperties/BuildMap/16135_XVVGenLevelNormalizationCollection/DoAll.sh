for i in 0 # 0 13 14
do
   echo $i
   for j in A B C D E F G H I J K L M
   do
      echo "   $j"
      cat SResult/* | grep ^T$j | ./a.out ${i}TeV
      cat SResult/* | grep ^V$j | ./a.out ${i}TeV
      cat BResult/* | grep ^T$j | ./a.out ${i}TeV
      cat BResult/* | grep ^V$j | ./a.out ${i}TeV
   done
done

