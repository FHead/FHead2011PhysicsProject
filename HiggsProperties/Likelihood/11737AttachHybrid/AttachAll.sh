#!/bin/sh

for i in EventF.root
do
   ./AttachBranch BranchCentralSignal Temp/SynthesizedLog_${i}_Central.txt $i
   ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_${i}_BCentral.txt $i
   ./AttachBranch BranchUpSignal Temp/SynthesizedLog_${i}_LeptonUp.txt $i
   ./AttachBranch BranchUpBackground Temp/SynthesizedLog_${i}_BLeptonUp.txt $i
   ./AttachBranch BranchDownSignal Temp/SynthesizedLog_${i}_LeptonDown.txt $i
   ./AttachBranch BranchDownBackground Temp/SynthesizedLog_${i}_BLeptonDown.txt $i
   ./AttachBranch BranchWideSignal Temp/SynthesizedLog_${i}_LeptonWide.txt $i
   ./AttachBranch BranchWideBackground Temp/SynthesizedLog_${i}_BLeptonWide.txt $i
   ./AttachBranch BranchNarrowSignal Temp/SynthesizedLog_${i}_LeptonNarrow.txt $i
   ./AttachBranch BranchNarrowBackground Temp/SynthesizedLog_${i}_BLeptonNarrow.txt $i
done


