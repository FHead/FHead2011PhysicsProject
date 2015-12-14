#!/bin/sh

mkdir -p Temp

for i0 in `seq 160001 160100`
do
   i="Events_$i0.root"
   echo $i
   for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
      BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   do
      cat BatchSubmit/$i/LSFJOB*/STDOUT | grep "$i " | grep " $j " \
         | grep -v nan \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done

   cp Source/$i .

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

   mv $i Destination/

   rm Temp/SynthesizedLog_${i}_*.txt
done


