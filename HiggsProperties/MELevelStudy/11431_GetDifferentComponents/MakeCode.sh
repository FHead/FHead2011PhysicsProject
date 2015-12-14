#!/bin/bash

echo > Code.cpp
echo > Code.h

for i in Expression*
do
   j=`echo $i | sed "s/Expression_//g"`
   l1=
   l2=
   for k in `echo $i | sed "s/Expression_//g" | sed "s/_/ /g" | tr ' ' '\n' | uniq`
   do
      l1="${l1}double $k = 1, "
      l2="${l2}double $k, "
   done

   echo "double GetGeneralScalar_$j(LeptonVectors &leptons, ${l1}bool UpType = false);" >> Code.h
   
   echo "double GetGeneralScalar_$j(LeptonVectors &leptons, ${l2}bool UpType)" >> Code.cpp
   echo "{" >> Code.cpp
   cat Header.txt >> Code.cpp
   echo "" >> Code.cpp
   echo "   return `cat $i`;" >> Code.cpp
   echo "}" >> Code.cpp
   echo >> Code.cpp
done



