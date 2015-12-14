#!/bin/sh

DatasetSize=250

sh compile.sh

for DatasetSize in 20 30 50 75 100 200 500 1000
do
   # for i in 1 2 3
   # do
   #    for j in N1 N2 N3 N4 P1 P2 P3 P4 P5
   #    do
   #       time ./PerformFit EventXi${i}${j}.root $DatasetSize
   #       mv OutputFile.root OutputFile_Xi${i}${j}_$DatasetSize.root
   #    done
   # done

   time ./PerformFit EventB.root $DatasetSize
   mv OutputFile.root Processing/OutputFile_B_$DatasetSize.root
done

mv OutputFile_Xi*root Processing/


