#!/bin/sh

for i in `ls Output/`
do
   echo $i

   InputString=
   for j in `ls Output/$i/*/*/*/0000/*root`
   do
      InputString="$InputString\"file:$j\","
   done

   if [ ! -z "$InputString" ]
   then
      InputString=${InputString::${#InputString}-1}

      FileName="Merge_${i}.py"
      OutputBase="${i}"

      sed "s#__INPUT__#$InputString#" < Merge_Template.py.txt \
         | sed "s#__OUTPUTBASE__#$OutputBase#" > $FileName
   fi
done
