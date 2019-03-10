#!/bin/sh

SampleBase=/afs/cern.ch/user/c/chenyi/EOS/cms/store/cmst3/user/botta/L1UpgradeNtuple/CMSSW_6_2_0_SLHC12/

ls -l $SampleBase/Neutrinos200PU/* | awk '{if($5>1000) print $9}' > SampleNu200.txt
ls -l $SampleBase/TTBar140PU/* | awk '{if($5>1000) print $9}' > SampleTT140.txt
ls -l $SampleBase/TTBar200PU/* | awk '{if($5>1000) print $9}' > SampleTT200.txt

for MenuFile in L1Menu_trkL1TDREta_v3p4.xml # L1Menu_std.txt L1Menu_trk.txt L1Menu_v19m20_std.txt L1Menu_trkL1TDREta_v3p4.xml
do
   for Type in Nu200 TT140 TT200
   do
      Base=${MenuFile/.txt}
      Base=${Base/.xml}
      Tag=${Base}_$Type

      echo Now Running with tag $Tag

      l1menuCreateReducedSample $MenuFile `cat Sample${Type}.txt`
      mv reducedSample.proto ${Tag}.proto

      l1menuCreateRatePlots --output ${Tag}.root ${Tag}.proto $MenuFile

      l1menuFitMenu --rateplots ${Tag}.root --output ${Tag}.xml ${Tag}.proto $MenuFile 180
      
      l1menuScaleMenuRates --rateplots ${Tag}.root --offlinescaling scaling/L12Offline_Fallback_95-85_LowPtMu_v5_uncalibratedJets_trkupdated.txt --format OLD ${Tag}.xml
   done
done
