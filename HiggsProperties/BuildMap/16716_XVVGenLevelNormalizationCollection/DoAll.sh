for i in 0 # 0 13 14
do
   echo $i
   for j in A B C D E F G H I J K L M N O P Q R S T
   do
      echo "   $j"
      bzcat SResult/*bz2 | grep ^T$j | ./a.out ${i}TeV
      bzcat SResult/*bz2 | grep ^V$j | ./a.out ${i}TeV
      # cat BResult/* | grep ^T$j | ./a.out ${i}TeV
      # cat BResult/* | grep ^V$j | ./a.out ${i}TeV
   done
done

