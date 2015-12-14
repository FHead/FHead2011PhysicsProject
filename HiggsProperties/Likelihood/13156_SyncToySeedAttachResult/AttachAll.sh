#!/bin/sh

cp OriginalTrees/*Data*7TeV* Destination/

for i in Destination/*Data*7TeV*
do
   echo $i
   j=`echo $i | sed "s#Destination/##g"`
   echo ./AttachBranch BranchCentralSignal             Temp/SynthesizedLog_${j}_Central.txt          $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchCentralBackground         Temp/SynthesizedLog_${j}_BCentral.txt         $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchUpSignal                  Temp/SynthesizedLog_${j}_LeptonUp.txt         $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchUpBackground              Temp/SynthesizedLog_${j}_BLeptonUp.txt        $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchDownSignal                Temp/SynthesizedLog_${j}_LeptonDown.txt       $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchDownBackground            Temp/SynthesizedLog_${j}_BLeptonDown.txt      $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchWideSignal                Temp/SynthesizedLog_${j}_LeptonWide.txt       $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchWideBackground            Temp/SynthesizedLog_${j}_BLeptonWide.txt      $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchNarrowSignal              Temp/SynthesizedLog_${j}_LeptonNarrow.txt     $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchNarrowBackground          Temp/SynthesizedLog_${j}_BLeptonNarrow.txt    $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchSpectrumHardSignal        Temp/SynthesizedLog_${j}_SpectrumHard.txt     $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchSpectrumHardBackground    Temp/SynthesizedLog_${j}_BSpectrumHard.txt    $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchSpectrumSoftSignal        Temp/SynthesizedLog_${j}_SpectrumSoft.txt     $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchSpectrumSoftBackground    Temp/SynthesizedLog_${j}_BSpectrumSoft.txt    $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchSpectrumCentralSignal     Temp/SynthesizedLog_${j}_SpectrumCentral.txt  $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchSpectrumCentralBackground Temp/SynthesizedLog_${j}_BSpectrumCentral.txt $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchSpectrumForwardSignal     Temp/SynthesizedLog_${j}_SpectrumForward.txt  $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchSpectrumForwardBackground Temp/SynthesizedLog_${j}_BSpectrumForward.txt $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchHMassASignal              Temp/SynthesizedLog_${j}_HMassA.txt           $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchHMassBSignal              Temp/SynthesizedLog_${j}_HMassB.txt           $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchHMassCSignal              Temp/SynthesizedLog_${j}_HMassC.txt           $i DuplicateEventMapping_7TeV.txt
   echo ./AttachBranch BranchHMassDSignal              Temp/SynthesizedLog_${j}_HMassD.txt           $i DuplicateEventMapping_7TeV.txt
done


echo "For sync toys, make sure it's combined log"

