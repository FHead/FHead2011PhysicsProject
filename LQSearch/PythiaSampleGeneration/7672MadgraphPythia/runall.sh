#!/bin/sh

BaseDir=/data1/yichen/Madgraph/Madgraph5_v1_4_3/7672_InclusiveWJJ

sh compile.sh ConvertToPlainTree.cpp Step1
~/RootMacros/CompileRootMacro ConvertTo7621Tree.cpp Step2

mkdir -p $BaseDir/PlainTree
mkdir -p $BaseDir/7621Tree

for i in `seq 49 50`
do
   j=`printf "%02d" $i`
   ./Step1 $BaseDir/Events/run_$j/tag_1_delphes_events.root $BaseDir/PlainTree/run_$j.root
   ./Step2 $BaseDir/PlainTree/run_$j.root $BaseDir/7621Tree/run_$j.root
done

hadd -f All7621Tree.root $BaseDir/7621Tree/run_*

fin



