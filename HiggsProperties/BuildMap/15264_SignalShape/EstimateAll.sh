#!/bin/sh

for i in s1 T1 V1 t1 v1
do
   echo -n "$i "

   for j in `seq 3 2 15`
   do
      cat BatchResult/* | grep "^$i " | awk "{print \$$j}" | grep -v "nan" \
         | ./a.out | tail -1 | awk '{print $7}' | tr -d '\n'
      echo -n " "
   done

   echo
done

exit

for i in 1 
do
   echo -n "T$i "

   for j in `seq 3 93`
   do
      cat BatchResult/* | grep "T$i " | awk "{print \$$j}" | ./a.out | tail -2 | awk '{print $7}'
   done

   echo
done





