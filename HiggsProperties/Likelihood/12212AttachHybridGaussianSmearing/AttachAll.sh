#!/bin/sh

# for i in EventF.root EventGd.root \
#    EventXi1N1.root EventXi1N2.root EventXi1N3.root EventXi1N4.root \
#    EventXi1P1.root EventXi1P2.root EventXi1P3.root EventXi1P4.root EventXi1P5.root \
#    EventXi2N1.root EventXi2N2.root EventXi2N3.root EventXi2N4.root \
#    EventXi2P1.root EventXi2P2.root EventXi2P3.root EventXi2P4.root EventXi2P5.root
# for i in EventXi2N1.root EventXi2N2.root EventXi2N3.root EventXi2N4.root \
#    EventXi2P1.root EventXi2P2.root EventXi2P3.root EventXi2P4.root EventXi2P5.root \
#    EventXi3N1.root EventXi3N2.root EventXi3N3.root EventXi3N4.root \
#    EventXi3P1.root EventXi3P2.root EventXi3P3.root EventXi3P4.root
for i in GenEventB.root 
do
   j=$i
   # j=`echo $i | sed "s/.root/Meow.root/g"`
   ./AttachBranch BranchCentralSignal Temp/SynthesizedLog_${i}_Central.txt $j
   ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_${i}_BCentral.txt $j
   ./AttachBranch BranchUpSignal Temp/SynthesizedLog_${i}_LeptonUp.txt $j
   ./AttachBranch BranchUpBackground Temp/SynthesizedLog_${i}_BLeptonUp.txt $j
   ./AttachBranch BranchDownSignal Temp/SynthesizedLog_${i}_LeptonDown.txt $j
   ./AttachBranch BranchDownBackground Temp/SynthesizedLog_${i}_BLeptonDown.txt $j
   ./AttachBranch BranchWideSignal Temp/SynthesizedLog_${i}_LeptonWide.txt $j
   ./AttachBranch BranchWideBackground Temp/SynthesizedLog_${i}_BLeptonWide.txt $j
   ./AttachBranch BranchNarrowSignal Temp/SynthesizedLog_${i}_LeptonNarrow.txt $j
   ./AttachBranch BranchNarrowBackground Temp/SynthesizedLog_${i}_BLeptonNarrow.txt $j
done


