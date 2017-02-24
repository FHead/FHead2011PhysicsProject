#!/bin/sh

# ln -s /afs/cern.ch/user/c/chenyi/EOS/cms/store/cmst3/user/chenyi/BTagTriggerPA2016/15542_0001_MinBias/ReggeGribovPartonMC_EposLHC_pPb_4080_4080/crab_20160927_101423/160927_081454/0000/log// log

mkdir -p Unpacked

for i in log/*.tar.gz
do
   echo $i
   tar zxvf $i "cmsRun-stdout-*"
   x=`ls cmsRun-stdout-*.log`
   grep "TrigReport" $x > Unpacked/$x
   rm $x
done

# for i in \
#    HLT_PAAK4CaloBJetCSV40_Eta2p1_v1 HLT_PAAK4PFBJetCSV40_Eta2p1_v1 HLT_PAAK4PFBJetCSV40_CommonTracking_Eta2p1_v1\
#    HLT_PAAK4CaloBJetCSV60_Eta2p1_v1 HLT_PAAK4PFBJetCSV60_Eta2p1_v1 HLT_PAAK4PFBJetCSV60_CommonTracking_Eta2p1_v1\
#    HLT_PAAK4CaloBJetCSV80_Eta2p1_v1 HLT_PAAK4PFBJetCSV80_Eta2p1_v1 HLT_PAAK4PFBJetCSV80_CommonTracking_Eta2p1_v1\
#    HLT_PAAK4CaloJet40_Eta2p1_v1 HLT_PAAK4PFJet40_Eta2p1_v1 \
#    HLT_PAAK4CaloJet60_Eta2p1_v1 HLT_PAAK4PFJet60_Eta2p1_v1 \
#    HLT_PAAK4CaloJet80_Eta2p1_v1 HLT_PAAK4PFJet80_Eta2p1_v1 \
#    HLT_PAAK4CaloJet40_Eta5p1_v2 HLT_PAAK4PFJet40_Eta5p1_v2 \
#    HLT_PAAK4CaloJet60_Eta5p1_v2 HLT_PAAK4PFJet60_Eta5p1_v2 \
#    HLT_PAAK4CaloJet80_Eta5p1_v2 HLT_PAAK4PFJet80_Eta5p1_v2 \
#    HLT_PAAK4CaloJet100_Eta5p1_v2 HLT_PAAK4PFJet100_Eta5p1_v2 \
#    HLT_PAAK4CaloJet40_Eta1p9toEta5p1_v2 HLT_PAAK4PFJet40_Eta1p9toEta5p1_v2 \
#    HLT_PAAK4CaloJet60_Eta1p9toEta5p1_v2 HLT_PAAK4PFJet60_Eta1p9toEta5p1_v2 \
#    HLT_PAAK4CaloJet40_Eta2p9toEta5p1_v2 HLT_PAAK4PFJet40_Eta2p9toEta5p1_v2 \
#    HLT_PAAK4CaloJet30_Eta5p1_PAL3Mu3_v2 HLT_PAAK4CaloJet30_Eta5p1_PAL3Mu5_v2 \
#    HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu3_v2 HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu5_v2 \
#    HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu3_v2 HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu5_v2 \
#    HLT_PADiAK4CaloJetAve40_Eta5p1_v2 HLT_PADiAK4PFJetAve40_Eta5p1_v2 \
#    HLT_PADiAK4CaloJetAve60_Eta5p1_v2 HLT_PADiAK4PFJetAve60_Eta5p1_v2 \
#    HLT_PADiAK4CaloJetAve80_Eta5p1_v2 HLT_PADiAK4PFJetAve80_Eta5p1_v2 \
#    HLT_PASinglePhoton10_Eta3p1_v2 HLT_PAPhoton10_Eta3p1_PPStyle_v6 \
#    HLT_PASinglePhoton15_Eta3p1_v2 HLT_PAPhoton15_Eta3p1_PPStyle_v6 \
#    HLT_PASinglePhoton20_Eta3p1_v2 HLT_PAPhoton20_Eta3p1_PPStyle_v6 \
#    HLT_PASinglePhoton30_Eta3p1_v2 HLT_PAPhoton30_Eta3p1_PPStyle_v6 \
#    HLT_PASinglePhoton40_Eta3p1_v2 HLT_PAPhoton40_Eta3p1_PPStyle_v6 \
#    HLT_PASingleIsoPhoton20_Eta3p1_v2 HLT_PAIsoPhoton20_Eta3p1_PPStyle_v6 \
#    HLT_PADoublePhoton15_Eta3p1_Mass50_1000_v2 \
#    HLT_PASinglePhoton10_Eta3p1_PAL3Mu3_v2 HLT_PASinglePhoton10_Eta3p1_PAL3Mu5_v2 \
#    HLT_PASinglePhoton15_Eta3p1_PAL3Mu3_v2 HLT_PASinglePhoton15_Eta3p1_PAL3Mu5_v2 \
#    HLT_PASinglePhoton20_Eta3p1_PAL3Mu3_v2 HLT_PASinglePhoton20_Eta3p1_PAL3Mu5_v2 \
#    HLT_Ele20_WPLoose_Gsf_v6

for i in HLT_PAAK4CaloJet40_Eta5p1_v \
   HLT_PAAK4CaloJet60_Eta5p1_v \
   HLT_PAAK4CaloJet80_Eta5p1_v \
   HLT_PAAK4CaloJet100_Eta5p1_v \
   HLT_PAAK4CaloJet40_Eta1p9toEta5p1_v \
   HLT_PAAK4CaloJet60_Eta1p9toEta5p1_v \
   HLT_PAAK4CaloJet40_Eta2p9toEta5p1_v \
   HLT_PAAK4CaloJet30_Eta5p1_PAL3Mu3_v \
   HLT_PAAK4CaloJet30_Eta5p1_PAL3Mu5_v \
   HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu3_v \
   HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu5_v \
   HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu3_v \
   HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu5_v \
   HLT_PAAK4PFJet40_Eta5p1_v \
   HLT_PAAK4PFJet60_Eta5p1_v \
   HLT_PAAK4PFJet80_Eta5p1_v \
   HLT_PAAK4PFJet100_Eta5p1_v \
   HLT_PAAK4PFJet40_Eta1p9toEta5p1_v \
   HLT_PAAK4PFJet60_Eta1p9toEta5p1_v \
   HLT_PAAK4PFJet40_Eta2p9toEta5p1_v \
   HLT_PADiAK4CaloJetAve40_Eta5p1_v \
   HLT_PADiAK4CaloJetAve60_Eta5p1_v \
   HLT_PADiAK4CaloJetAve80_Eta5p1_v \
   HLT_PADiAK4PFJetAve40_Eta5p1_v \
   HLT_PADiAK4PFJetAve60_Eta5p1_v \
   HLT_PADiAK4PFJetAve80_Eta5p1_v \
   HLT_PASinglePhoton10_Eta3p1_v \
   HLT_PASinglePhoton15_Eta3p1_v \
   HLT_PASinglePhoton20_Eta3p1_v \
   HLT_PASinglePhoton30_Eta3p1_v \
   HLT_PASinglePhoton40_Eta3p1_v \
   HLT_PASingleIsoPhoton20_Eta3p1_v \
   HLT_PADoublePhoton15_Eta3p1_Mass50_1000_v \
   HLT_PASinglePhoton10_Eta3p1_PAL3Mu3_v \
   HLT_PASinglePhoton10_Eta3p1_PAL3Mu5_v \
   HLT_PASinglePhoton15_Eta3p1_PAL3Mu3_v \
   HLT_PASinglePhoton15_Eta3p1_PAL3Mu5_v \
   HLT_PASinglePhoton20_Eta3p1_PAL3Mu3_v \
   HLT_PASinglePhoton20_Eta3p1_PAL3Mu5_v \
   HLT_PAPhoton10_Eta3p1_PPStyle_v \
   HLT_PAPhoton15_Eta3p1_PPStyle_v \
   HLT_PAPhoton20_Eta3p1_PPStyle_v \
   HLT_PAPhoton30_Eta3p1_PPStyle_v \
   HLT_PAPhoton40_Eta3p1_PPStyle_v \
   HLT_PAIsoPhoton20_Eta3p1_PPStyle_v \
   HLT_PAAK4CaloBJetCSV40_Eta2p1_v \
   HLT_PAAK4CaloBJetCSV60_Eta2p1_v \
   HLT_PAAK4CaloBJetCSV80_Eta2p1_v \
   HLT_PAAK4PFBJetCSV40_Eta2p1_v \
   HLT_PAAK4PFBJetCSV60_Eta2p1_v \
   HLT_PAAK4PFBJetCSV80_Eta2p1_v \
   HLT_PAAK4PFBJetCSV40_CommonTracking_Eta2p1_v \
   HLT_PAAK4PFBJetCSV60_CommonTracking_Eta2p1_v \
   HLT_PAAK4PFBJetCSV80_CommonTracking_Eta2p1_v \
   HLT_PAEle20_WPLoose_Gsf_v
do
   # echo $i
   MEOW=`grep "$i[0-9]$" Unpacked/*log | \
      grep TrigReport | \
      awk '{SUM += $4; PASS += $5} END { print PASS,SUM}'`
   MEOW2="`~/work/PhysicsWorkspace/PAPreparation2016/Trigger/15542_UpperLimitOnRate/a.out $MEOW`"
   echo "$i $MEOW $MEOW2"
done | tee Result.txt


