#!/bin/sh

for i in `ls NewTrees/ | grep root | grep 8TeV | sed "s/.root//g"`
do
   echo $i
   echo ./AttachBranch BranchCentralSignal Temp/SynthesizedLog_${i}_Seed.root_Signal_0_Central.txt NewTrees/$i.root 
   ./AttachBranch BranchCentralSignal Temp/SynthesizedLog_${i}_Seed.root_Signal_0_Central.txt NewTrees/$i.root 
   echo ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_${i}_Seed.root__Background_0_BCentral.txt NewTrees/$i.root 
   ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_${i}_Seed.root_Background_0_BCentral.txt NewTrees/$i.root 
done


