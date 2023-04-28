#!/bin/bash

WorkDir=$1
GenIndex=$2
HLTIndex=$3

cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_12_4_9/src
eval `scramv1 runtime -sh`
cd $WorkDir

mkdir -p /tmp/chenyi/

time ./Execute --GenInput GenParticles/HiForestMiniAOD_${GenIndex}.root \
   --HLTInput HLTTree/${HLTIndex}.root \
   --Output /tmp/chenyi/JRAPF_${GenIndex}_${HLTIndex}.root \
   --HLTObjectTreeName "hltobject/HLT_HICsAK4PFJet60Eta1p5_v" \
   --Directory "ak4pf"
time ./Execute --GenInput GenParticles/HiForestMiniAOD_${GenIndex}.root \
   --HLTInput HLTTree/${HLTIndex}.root \
   --Output /tmp/chenyi/JRACalo_${GenIndex}_${HLTIndex}.root \
   --HLTObjectTreeName "hltobject/HLT_HIPuAK4CaloJet40Eta5p1_v" \
   --Directory "ak4calo"

hadd /tmp/chenyi/JRA_${GenIndex}_${HLTIndex}.root \
   /tmp/chenyi/JRAPF_${GenIndex}_${HLTIndex}.root \
   /tmp/chenyi/JRACalo_${GenIndex}_${HLTIndex}.root

mv /tmp/chenyi/JRA_${GenIndex}_${HLTIndex}.root Output/
rm /tmp/chenyi/JRAPF_${GenIndex}_${HLTIndex}.root
rm /tmp/chenyi/JRACalo_${GenIndex}_${HLTIndex}.root

