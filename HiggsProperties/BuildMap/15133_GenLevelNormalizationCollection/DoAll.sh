for i in 0 13 14
do
   echo $i
   for j in A B C D E F G H I J K L M
   do
      echo "   $j"
      cat SResult/*_${i}TeV_* | grep ^T$j | ./a.out ${i}TeV
      cat SResult/*_${i}TeV_* | grep ^V$j | ./a.out ${i}TeV
      cat BResult/*_${i}TeV_* | grep ^T$j | ./a.out ${i}TeV
      cat BResult/*_${i}TeV_* | grep ^V$j | ./a.out ${i}TeV
   done
done

