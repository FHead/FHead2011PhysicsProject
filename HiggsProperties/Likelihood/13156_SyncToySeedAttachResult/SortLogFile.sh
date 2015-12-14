#!/bin/sh

mkdir -p Temp

for i in `ls Source/ | grep Data | grep 8TeV`
do
   echo $i
   # for j in BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow \
   #    BSpectrumHard BSpectrumSoft BSpectrumCentral BSpectrumForward
   for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
      BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow \
      SpectrumHard SpectrumSoft SpectrumCentral SpectrumForward \
      BSpectrumHard BSpectrumSoft BSpectrumCentral BSpectrumForward \
      HMassA HMassB HMassC HMassD
   # for j in Central 
   do
      cat BatchResult/DataManualFile* BatchResult/${i}_*/Result*.txt \
         | grep "$i " | grep " $j " \
         | grep -v nan \
         | cut --delim=' ' --field=3- \
         | sort -n > Temp/SynthesizedLog_${i}_${j}.txt
   done
done


