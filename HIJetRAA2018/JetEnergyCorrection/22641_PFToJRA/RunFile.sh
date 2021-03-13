#!/bin/bash

WorkDir=$1
Input=$2
Output=$3
ExcludeHEM=$4

cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_10_3_5/src
eval `scramv1 runtime -sh`
cd -

cp $WorkDir/Execute .

./Execute --Input $Input --Output JRA.root --ExcludeHEM $ExcludeHEM
mv JRA.root $Output

rm Execute
