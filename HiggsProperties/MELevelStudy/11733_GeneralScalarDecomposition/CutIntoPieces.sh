#!/bin/sh

Counter=0

File=ReplacedGeneralScalar.txt

PreviousLocation=0
for i in `cat -n $File | grep @ | awk '{print $1}'`
do
   Counter=`echo $Counter | AddConst 1`

   CurrentLocation=$i
   Difference=`echo $CurrentLocation | SubtractConst $PreviousLocation`

   echo $PreviousLocation $CurrentLocation $Difference

   head -n$CurrentLocation $File | tail -n$Difference | grep -v "@" > Parts_$Counter.txt

   PreviousLocation=$CurrentLocation
done



