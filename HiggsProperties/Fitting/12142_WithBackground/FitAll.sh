#!/bin/sh

DatasetSize=1000
BackgroundDatasetSize=200

sh compile.sh

for i in 1 2 3
do
   for j in N1 N2 N3 N4 P1 P2 P3 P4 P5
   do
      time ./PerformFit EventXi${i}${j}.root $DatasetSize Madgraph_part1.root $BackgroundDatasetSize
      mv OutputFile.root OutputFile_Xi${i}${j}.root
   done
done

time ./PerformFit EventB.root $DatasetSize Madgraph_part1.root $BackgroundDatasetSize

mv OutputFile.root Processing/OutputFile_B.root
mv OutputFile_Xi*root Processing/


