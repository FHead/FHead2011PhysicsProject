for i in A1ZZ
do
   for j in A B C D E F G H I J K
   do
      for k in Both # BothS EMS EES #Both EM EE
      do
         mkdir -p Plots/$i/$j/$k/
         ./a.out Result${k}_${i}_${j}_
         mv A[234][ZA][ZA]-*A4ZZ.* Plots/$i/$j/$k/
         mv F[EM][EM]-*A4ZZ.* Plots/$i/$j/$k/
      done
   done
done
