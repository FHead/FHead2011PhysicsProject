#!/bin/sh

for i in `seq 221 265`
do
   i=Events_210$i.root
   echo $i
   j=$i
   cp CleanTrees/$j .
   # j=`echo $i | sed "s/.root/Meow.root/g"`
   ./AttachBranch BranchList Temp/SynthesizedLog_${i}_Central.txt $j

   mv $j Destination/
done


