#!/bin/sh

for j in 7
do
   for i in `seq 10 2 70`
   do
      ./a.out 0.$i $j
   done > log$j

   grep RESULTEXP1 log$j | cut -d ' ' -f 2-4 > Exp1_$j
   grep RESULTEXP2 log$j | cut -d ' ' -f 2-4 > Exp2_$j

   echo "{" > convert.C
   echo "   gSystem->Load(\"PlotThreeColumnFile_C.so\");" >> convert.C
   echo "" >> convert.C
   echo "   PlotThreeColumnFile(\"Exp1_$j\", \"Exp1_$j.root\");" >> convert.C
   echo "   PlotThreeColumnFile(\"Exp2_$j\", \"Exp2_$j.root\");" >> convert.C
   echo "}" >> convert.C

   root -l -b -q convert.C

   rm convert.C
done

./b.out


