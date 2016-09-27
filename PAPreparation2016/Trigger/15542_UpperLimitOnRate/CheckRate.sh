#!/bin/sh

mkdir -p Unpacked

for i in log/*.tar.gz
do
   echo $i
   # tar zxvf $i
   # rm Framework*xml
   # rm cmsRun-stderr-*.log
   # mv cmsRun-stdout-*.log Unpacked
done

for i in \
   HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1 HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1 HLT_PAAK4PFBJetCSV60_Eta2p1_v1 \
   HLT_PAAK4CaloBJetCSVv180_Eta2p1_v1 HLT_PAAK4CaloBJetCSVv280_Eta2p1_v1 HLT_PAAK4PFBJetCSV80_Eta2p1_v1 \
   HLT_PAAK4CaloBJetCSVv1100_Eta2p1_v1 HLT_PAAK4CaloBJetCSVv2100_Eta2p1_v1 HLT_PAAK4PFBJetCSV100_Eta2p1_v1
do
   MEOW=`grep "$i$" Unpacked/*log | \
      grep TrigReport | \
      awk '{SUM += $4; PASS += $5} END { print PASS,SUM}'`
   MEOW2=`~/work/PhysicsWorkspace/PAPreparation2016/Trigger/15542_UpperLimitOnRate/a.out $MEOW`
   echo "$i $MEOW $MEOW2"
done
