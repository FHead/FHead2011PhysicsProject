#!/bin/sh

SampleBase=/afs/cern.ch/user/c/chenyi/EOS/cms/store/cmst3/user/botta/L1UpgradeNtuple/CMSSW_6_2_0_SLHC12/
MenuFile=L1Menu_trk.txt

ls -l $SampleBase/Neutrinos200PU/* | awk '{if($5>1000) print $9}' > SampleNu200.txt
ls -l $SampleBase/TTBar140PU/* | awk '{if($5>1000) print $9}' > SampleTT140.txt
ls -l $SampleBase/TTBar200PU/* | awk '{if($5>1000) print $9}' > SampleTT200.txt

for Tag in Nu200 TT140 TT200
do
   l1menuCreateReducedSample $MenuFile `cat Sample${Tag}.txt`
   mv reducedSample.proto ${Tag}.proto

   l1menuCreateRatePlots --output ${Tag}.root ${Tag}.proto $MenuFile

   # l1menuFitMenu --rateplots output_rates_PU140_v22.root --output georgiaUnscaled.xml reducedSample.proto L1Menu_v19m20_std.txt 100
   # l1menuScaleMenuRates --rateplots output_rates_PU140_v22.root --muonscaling MuonScales_Scale_Iso50PU_3pt.root --datascaling output_rates_Fallback_Run2012C_ZeroBias_PU66_v22.root --montecarloscaling output_rates_FallBack_NeutrinoGun_8TeV_PU66_v22.root --offlinescaling L12Offline_Fallback_95-85_LowPtMu_v5_uncalibratedJets_updated.txt --format OLD georgiaUnscaled.xml
done

