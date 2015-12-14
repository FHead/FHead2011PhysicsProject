#!/bin/sh

DatasetSize=20

sh compile.sh

./PerformFit EventXi1P1.root $DatasetSize 1 0 0 1.624598482 0
mv OutputFile.root OutputFile_Xi1P1.root
./PerformFit EventXi1P2.root $DatasetSize 1 0 0 3.632812640 0
mv OutputFile.root OutputFile_Xi1P2.root
./PerformFit EventXi1P3.root $DatasetSize 1 0 0 6.881909605 0
mv OutputFile.root OutputFile_Xi1P3.root
./PerformFit EventXi1P4.root $DatasetSize 1 0 0 15.38841767 0
mv OutputFile.root OutputFile_Xi1P4.root
./PerformFit EventXi1P5.root $DatasetSize 1 0 0 10000000000 0
mv OutputFile.root OutputFile_Xi1P5.root
./PerformFit EventXi1N1.root $DatasetSize 1 0 0 -1.624598482 0
mv OutputFile.root OutputFile_Xi1N1.root
./PerformFit EventXi1N2.root $DatasetSize 1 0 0 -3.632812640 0
mv OutputFile.root OutputFile_Xi1N2.root
./PerformFit EventXi1N3.root $DatasetSize 1 0 0 -6.881909605 0
mv OutputFile.root OutputFile_Xi1N3.root
./PerformFit EventXi1N4.root $DatasetSize 1 0 0 -15.38841767 0
mv OutputFile.root OutputFile_Xi1N4.root
./PerformFit EventB.root $DatasetSize 1 0 0 0 0
mv OutputFile.root OutputFile_B.root

mv OutputFile_B.root Processing/OutputFile_B.root
mv OutputFile_Xi*root Processing/

rm Processing/OutputFile_All.root
hadd -f Processing/OutputFile_All.root Processing/OutputFile_*.root


