#!/bin/sh

# ln -s /afs/cern.ch/user/c/chenyi/EOS/cms/store/cmst3/user/chenyi/BTagTriggerPA2016/15542_0001_MinBias/ReggeGribovPartonMC_EposLHC_pPb_4080_4080/crab_20160927_101423/160927_081454/0000/log// log

mkdir -p Unpacked

# for i in log/*.tar.gz
# do
#    echo $i
#    tar zxvf $i "cmsRun-stdout-*"
#    mv cmsRun-stdout-*.log Unpacked/
# done

for i in \
   HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1 HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1 HLT_PAAK4PFBJetCSV60_Eta2p1_v1 \
   HLT_PAAK4CaloBJetCSVv180_Eta2p1_v1 HLT_PAAK4CaloBJetCSVv280_Eta2p1_v1 HLT_PAAK4PFBJetCSV80_Eta2p1_v1 \
   HLT_PAAK4CaloBJetCSVv1100_Eta2p1_v1 HLT_PAAK4CaloBJetCSVv2100_Eta2p1_v1 HLT_PAAK4PFBJetCSV100_Eta2p1_v1 \
   HLT_PAAK4CaloJet60_Eta2p1_v1 HLT_PAAK4PFJet60_Eta2p1_v1 \
   HLT_PAAK4CaloJet80_Eta2p1_v1 HLT_PAAK4PFJet80_Eta2p1_v1 \
   HLT_PAAK4CaloJet100_Eta2p1_v1 HLT_PAAK4PFJet100_Eta2p1_v1
do
   echo $i
   MEOW=`grep "$i$" Unpacked/*log | \
      grep TrigReport | \
      awk '{SUM += $4; PASS += $5} END { print PASS,SUM}'`
   MEOW2=`~/work/PhysicsWorkspace/PAPreparation2016/Trigger/15542_UpperLimitOnRate/a.out $MEOW`
   echo "$i $MEOW $MEOW2"
done
