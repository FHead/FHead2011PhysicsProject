#!/bin/sh

cp Source/*root /wntmp/yichen/

for i in `seq 1 3`
do
   ./AttachBranch BranchCentralSignal Temp/SynthesizedLog_12751_BackgroundRecoToys_12751_Run${i}_Seed.root_Signal_0_1_Central.txt /wntmp/yichen/Background${i}_EM.root
   ./AttachBranch BranchCentralSignal Temp/SynthesizedLog_12751_BackgroundRecoToys_12751_Run${i}_Seed.root_Signal_0_2_Central.txt /wntmp/yichen/Background${i}_ME.root
   ./AttachBranch BranchCentralSignal Temp/SynthesizedLog_12751_BackgroundRecoToys_12751_Run${i}_Seed.root_Signal_0_3_Central.txt /wntmp/yichen/Background${i}_EE.root
   ./AttachBranch BranchCentralSignal Temp/SynthesizedLog_12751_BackgroundRecoToys_12751_Run${i}_Seed.root_Signal_0_4_Central.txt /wntmp/yichen/Background${i}_MM.root
done

for i in `seq 1 4`
do
   ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_12744_SignalSplineProjection_12754_Toy${i}_Seed.root_Background_0_1_BCentral.txt /wntmp/yichen/Signal${i}_EM.root
   ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_12744_SignalSplineProjection_12754_Toy${i}_Seed.root_Background_0_2_BCentral.txt /wntmp/yichen/Signal${i}_ME.root
   ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_12744_SignalSplineProjection_12754_Toy${i}_Seed.root_Background_0_3_BCentral.txt /wntmp/yichen/Signal${i}_EE.root
   ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_12744_SignalSplineProjection_12754_Toy${i}_Seed.root_Background_0_4_BCentral.txt /wntmp/yichen/Signal${i}_MM.root
done



exit

for i in Signal*root
do
   echo $i
   j=$i
   # j=`echo $i | sed "s/.root/Meow.root/g"`
   #./AttachBranch BranchCentralSignal Temp/SynthesizedLog_${i}_Central.txt $j
   ./AttachBranch BranchCentralBackground Temp/SynthesizedLog_${i}_BCentral.txt $j
   #./AttachBranch BranchUpSignal Temp/SynthesizedLog_${i}_LeptonUp.txt $j
   #./AttachBranch BranchUpBackground Temp/SynthesizedLog_${i}_BLeptonUp.txt $j
   #./AttachBranch BranchDownSignal Temp/SynthesizedLog_${i}_LeptonDown.txt $j
   #./AttachBranch BranchDownBackground Temp/SynthesizedLog_${i}_BLeptonDown.txt $j
   #./AttachBranch BranchWideSignal Temp/SynthesizedLog_${i}_LeptonWide.txt $j
   #./AttachBranch BranchWideBackground Temp/SynthesizedLog_${i}_BLeptonWide.txt $j
   #./AttachBranch BranchNarrowSignal Temp/SynthesizedLog_${i}_LeptonNarrow.txt $j
   #./AttachBranch BranchNarrowBackground Temp/SynthesizedLog_${i}_BLeptonNarrow.txt $j
   #./AttachBranch BranchSpectrumHardSignal Temp/SynthesizedLog_${i}_SpectrumHard.txt $j
   #./AttachBranch BranchSpectrumHardBackground Temp/SynthesizedLog_${i}_BSpectrumHard.txt $j
   #./AttachBranch BranchSpectrumSoftSignal Temp/SynthesizedLog_${i}_SpectrumSoft.txt $j
   #./AttachBranch BranchSpectrumSoftBackground Temp/SynthesizedLog_${i}_BSpectrumSoft.txt $j
   #./AttachBranch BranchSpectrumCentralSignal Temp/SynthesizedLog_${i}_SpectrumCentral.txt $j
   #./AttachBranch BranchSpectrumCentralBackground Temp/SynthesizedLog_${i}_BSpectrumCentral.txt $j
   #./AttachBranch BranchSpectrumForwardSignal Temp/SynthesizedLog_${i}_SpectrumForward.txt $j
   #./AttachBranch BranchSpectrumForwardBackground Temp/SynthesizedLog_${i}_BSpectrumForward.txt $j
   #./AttachBranch BranchHMassASignal Temp/SynthesizedLog_${i}_HMassA.txt $j
   #./AttachBranch BranchHMassBSignal Temp/SynthesizedLog_${i}_HMassB.txt $j
   #./AttachBranch BranchHMassCSignal Temp/SynthesizedLog_${i}_HMassC.txt $j
   #./AttachBranch BranchHMassDSignal Temp/SynthesizedLog_${i}_HMassD.txt $j
done


