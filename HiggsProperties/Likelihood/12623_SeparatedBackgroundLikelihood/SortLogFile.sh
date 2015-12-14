#!/bin/sh

mkdir -p Temp

for i in `ls Source | grep 1125`
do
   echo $i
   for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
      BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow \
      SpectrumHard SpectrumSoft SpectrumCentral SpectrumForward \
      BSpectrumHard BSpectrumSoft BSpectrumCentral BSpectrumForward \
      HMassA HMassB HMassC HMassD
   do
      cat BatchSubmit/${i}/LSF*/STDOUT BatchSubmit/LSF*/STDOUT | grep "$i " | grep " $j " \
         | grep -v nan \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done


