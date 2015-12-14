for i in BCentral BLeptonDown BLeptonUp BLeptonWide BLeptonNarrow \
   BSpectrumHard BSpectrumSoft BSpectrumCentral BSpectrumForward
do
   for j in Bkg SMSignal ExoticSignal
   do
      ./CombineFiles \
         Temp/SynthesizedLog_SyncToys_7TeV_2e2mu_$j.root_$i.txt \
         Temp/SynthesizedLog_SyncToys_7TeV_2mu2e_$j.root_$i.txt \
         Temp/CombinedLog_SyncToys_7TeV_2e2mu_$j.root_$i.txt \
         0.838306379139608 0.525381326163067
      ./CombineFiles \
         Temp/SynthesizedLog_SyncToys_8TeV_2e2mu_$j.root_$i.txt \
         Temp/SynthesizedLog_SyncToys_8TeV_2mu2e_$j.root_$i.txt \
         Temp/CombinedLog_SyncToys_8TeV_2e2mu_$j.root_$i.txt \
         3.76890178716858 2.15926664889866
   done
done

for i in Central LeptonDown LeptonUp LeptonWide LeptonNarrow \
   SpectrumHard SpectrumSoft SpectrumCentral SpectrumForward \
   HMassA HMassB HMassC HMassD
do
   for j in Bkg SMSignal ExoticSignal
   do
      ./CombineFiles \
         Temp/SynthesizedLog_SyncToys_7TeV_2e2mu_$j.root_$i.txt \
         Temp/SynthesizedLog_SyncToys_7TeV_2mu2e_$j.root_$i.txt \
         Temp/CombinedLog_SyncToys_7TeV_2e2mu_$j.root_$i.txt \
         0.903698367186646 0.709841721668633
      ./CombineFiles \
         Temp/SynthesizedLog_SyncToys_8TeV_2e2mu_$j.root_$i.txt \
         Temp/SynthesizedLog_SyncToys_8TeV_2mu2e_$j.root_$i.txt \
         Temp/CombinedLog_SyncToys_8TeV_2e2mu_$j.root_$i.txt \
         4.43783616325471 3.44582607240994
   done
done







