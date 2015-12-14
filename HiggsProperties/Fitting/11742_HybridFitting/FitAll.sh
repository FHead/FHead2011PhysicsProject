#!/bin/sh

DatasetSize=300

CompileRootMacro DoFit.cpp
time ./a.out EventB.root $DatasetSize
mv OutputFile.root OutputFile_PureA1.root
time ./a.out EventC.root $DatasetSize
mv OutputFile.root OutputFile_PureA3.root
time ./a.out EventD.root $DatasetSize
mv OutputFile.root OutputFile_PureA2.root
time ./a.out EventF.root $DatasetSize
mv OutputFile.root OutputFile_EventF.root
time ./a.out EventGa.root $DatasetSize
mv OutputFile.root OutputFile_EventGa.root


