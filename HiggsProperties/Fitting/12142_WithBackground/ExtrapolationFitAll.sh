#!/bin/sh

DatasetSize=250
BackgroundDatasetSize=50

sh compile.sh

for DatasetSize in 20 30 40 50 60 70 80 90 100 150 200 300 400 500 600 700 800 900 1000
do
   BackgroundDatasetSize=`echo $DatasetSize | DivideConst 5`

   # for i in 1 2 3
   # do
   #    for j in N1 N2 N3 N4 P1 P2 P3 P4 P5
   #    do
   #       time ./PerformFit EventXi${i}${j}.root $DatasetSize
   #       mv OutputFile.root OutputFile_Xi${i}${j}_$DatasetSize.root
   #    done
   # done

   time ./PerformFit EventB.root $DatasetSize Madgraph_part1.root $BackgroundDatasetSize
   mv OutputFile.root Processing/OutputFile_B_$DatasetSize.root
done

mv OutputFile_Xi*root Processing/


