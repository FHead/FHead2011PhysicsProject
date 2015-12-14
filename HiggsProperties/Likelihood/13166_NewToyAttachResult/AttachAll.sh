#!/bin/sh

cp Source2/*Background* TempDestination/

for i in TempDestination/*Background*
do
   echo $i
   j=`echo $i | sed "s#TempDestination/##g"`
   ./AttachBranch BranchCentralSignal             Temp/SynthesizedLog_${j}_Central.txt          $i
   echo ./AttachBranch BranchCentralBackground         Temp/SynthesizedLog_${j}_BCentral.txt         $i
   echo ./AttachBranch BranchUpSignal                  Temp/SynthesizedLog_${j}_LeptonUp.txt         $i
   echo ./AttachBranch BranchUpBackground              Temp/SynthesizedLog_${j}_BLeptonUp.txt        $i
   echo ./AttachBranch BranchDownSignal                Temp/SynthesizedLog_${j}_LeptonDown.txt       $i
   echo ./AttachBranch BranchDownBackground            Temp/SynthesizedLog_${j}_BLeptonDown.txt      $i
   echo ./AttachBranch BranchWideSignal                Temp/SynthesizedLog_${j}_LeptonWide.txt       $i
   echo ./AttachBranch BranchWideBackground            Temp/SynthesizedLog_${j}_BLeptonWide.txt      $i
   echo ./AttachBranch BranchNarrowSignal              Temp/SynthesizedLog_${j}_LeptonNarrow.txt     $i
   echo ./AttachBranch BranchNarrowBackground          Temp/SynthesizedLog_${j}_BLeptonNarrow.txt    $i
   echo ./AttachBranch BranchSpectrumHardSignal        Temp/SynthesizedLog_${j}_SpectrumHard.txt     $i
   echo ./AttachBranch BranchSpectrumHardBackground    Temp/SynthesizedLog_${j}_BSpectrumHard.txt    $i
   echo ./AttachBranch BranchSpectrumSoftSignal        Temp/SynthesizedLog_${j}_SpectrumSoft.txt     $i
   echo ./AttachBranch BranchSpectrumSoftBackground    Temp/SynthesizedLog_${j}_BSpectrumSoft.txt    $i
   echo ./AttachBranch BranchSpectrumCentralSignal     Temp/SynthesizedLog_${j}_SpectrumCentral.txt  $i
   echo ./AttachBranch BranchSpectrumCentralBackground Temp/SynthesizedLog_${j}_BSpectrumCentral.txt $i
   echo ./AttachBranch BranchSpectrumForwardSignal     Temp/SynthesizedLog_${j}_SpectrumForward.txt  $i
   echo ./AttachBranch BranchSpectrumForwardBackground Temp/SynthesizedLog_${j}_BSpectrumForward.txt $i
   echo ./AttachBranch BranchHMassASignal              Temp/SynthesizedLog_${j}_HMassA.txt           $i
   echo ./AttachBranch BranchHMassBSignal              Temp/SynthesizedLog_${j}_HMassB.txt           $i
   echo ./AttachBranch BranchHMassCSignal              Temp/SynthesizedLog_${j}_HMassC.txt           $i
   echo ./AttachBranch BranchHMassDSignal              Temp/SynthesizedLog_${j}_HMassD.txt           $i
done


