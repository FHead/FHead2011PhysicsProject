#!/bin/sh

mkdir -p Temp

for i in `ls Source2/ `
do
   echo $i
   k=`echo $i | cut --delim='_' --field=1-5`
   l=`echo $i | cut --delim='_' --field=6`
   l=${l/.root}
   # for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
   #    BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow \
   #    SpectrumHard SpectrumSoft SpectrumCentral SpectrumForward \
   #    BSpectrumHard BSpectrumSoft BSpectrumCentral BSpectrumForward \
   #    HMassA HMassB HMassC HMassD
   for j in BCentral Central
   do
      cat BatchResult2/${k}*$l/Result*.txt \
         | grep "root" | grep " $j " \
         | grep -v nan \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done

   exit
done

exit




