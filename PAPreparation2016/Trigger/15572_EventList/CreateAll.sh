for i in HLT_*txt
do
   Tag=${i/.txt/}
   echo $Tag

   mkdir -p $Tag

   cd $Tag
   tr ',' '\n' < ../$i > Meow
   edmPickEvents.py "/ReggeGribovPartonMC_EposLHC_pPb_4080_4080/pPb816Summer16DR-80X_mcRun2_asymptotic_v15-v1/AODSIM" Meow --crab
   sed "s/__TAG__/$Tag/g" ../crab_template.py > pickevents_crab.py
   cd ..
done
