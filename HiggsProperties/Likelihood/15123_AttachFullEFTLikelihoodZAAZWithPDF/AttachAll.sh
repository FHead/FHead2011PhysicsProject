#!/bin/sh

for i in `ls CleanTrees | grep Prophecy`
do
   echo $i
   j=$i
   cp CleanTrees/$j .
   # j=`echo $i | sed "s/.root/Meow.root/g"`
   ./AttachBranch BranchCentralSignal Temp/SynthesizedLog_${i}_Central.txt $j
   ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_${i}_BCentral.txt $j
   # ./AttachBranch BranchUpSignal Temp/SynthesizedLog_${i}_LeptonUp.txt $j
   # ./AttachBranch BranchUpBackground Temp/SynthesizedLog_${i}_BLeptonUp.txt $j
   # ./AttachBranch BranchDownSignal Temp/SynthesizedLog_${i}_LeptonDown.txt $j
   # ./AttachBranch BranchDownBackground Temp/SynthesizedLog_${i}_BLeptonDown.txt $j
   # ./AttachBranch BranchWideSignal Temp/SynthesizedLog_${i}_LeptonWide.txt $j
   # ./AttachBranch BranchWideBackground Temp/SynthesizedLog_${i}_BLeptonWide.txt $j
   # ./AttachBranch BranchNarrowSignal Temp/SynthesizedLog_${i}_LeptonNarrow.txt $j
   # ./AttachBranch BranchNarrowBackground Temp/SynthesizedLog_${i}_BLeptonNarrow.txt $j

   mv $j ProphecyResult/
done


