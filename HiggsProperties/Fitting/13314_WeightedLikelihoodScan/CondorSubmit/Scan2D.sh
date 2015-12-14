#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_6_0_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/Fitting/13222_WeightedLikelihoodScan/
WorkDir=`pwd`

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

BinCount=32
BinMin=-0.999
BinMax=0.999

ID1=`echo $1 $BinCount | awk '{print $1 % $2 + 1}'`
ID2=`echo $1 $BinCount | awk '{print ($1 - ($1 % $2)) / $2 + 1}'`

F2=`echo $BinMin $BinMax $BinCount $ID1 | awk '{print $1 + ($2-$1)/($3-1)*($4-1)}'`
F3=`echo $BinMin $BinMax $BinCount $ID2 | awk '{print $1 + ($2-$1)/($3-1)*($4-1)}'`
FL=0
AbsF2=`echo $F2 | awk '{if($1<0) {print -$1} else {print $1}}'`
AbsF3=`echo $F3 | awk '{if($1<0) {print -$1} else {print $1}}'`
AbsFL=`echo $FL | awk '{if($1<0) {print -$1} else {print $1}}'`
F1=`echo $AbsF2 $AbsF3 $AbsFL | awk '{print 1-$1-$2-$3}'`
S2=`echo $F1 $F2 | awk '{print $2/$1}' | awk '{if($1 < 0) {print -$1} else {print $1}}'`
S3=`echo $F1 $F3 | awk '{print $2/$1}' | awk '{if($1 < 0) {print -$1} else {print $1}}'`
SL=`echo $F1 $FL | awk '{print $2/$1}' | awk '{if($1 < 0) {print -$1} else {print $1}}'`
A2=`echo $F2 $S2 | awk '{if($1 > 0) {print sqrt($2)*(-3.276)} else {print -sqrt($2)*(-3.276)}}'`
A3=`echo $F3 $S3 | awk '{if($1 > 0) {print sqrt($2)*(-5.042)} else {print -sqrt($2)*(-5.042)}}'`
AL=`echo $FL $SL | awk '{if($1 > 0) {print sqrt($2)*(-0.0001204601)} else {print -sqrt($2)*(-0.0001204601)}}'`

echo $F2 $F3 $FL
echo $A2 $A3 $AL

if [[ `echo "$F1 > 0" | bc` == "1" ]];
then

   echo Running with A2=$A2, A3=$A3, AL=$AL...

   cp -r $BaseDir/*cpp $WorkDir/
   cp -r $BaseDir/*h $WorkDir/
   cp -r $BaseDir/Trees $WorkDir/
   cp -r $BaseDir/OldTrees $WorkDir/
   cp -r $BaseDir/SyncTrees $WorkDir/

   rm $WorkDir/*.dh
   ln -s $BaseDir/../../BuildMap/13156_CollectNormalization/CombinedNormalization.dh $WorkDir/
   ln -s $BaseDir/../../BuildMap/13156_CollectNormalization/Normalization.dh $WorkDir/

   sh compile.sh

   # S7=Trees/SignalAll7TeV.root
   # B7=Trees/BackgroundAll7TeV.root
   # Z7=OldTrees/HZZEventFitFormat_MC_ZJets_8TeV.root
   # G7=OldTrees/HZZEventFitFormat_ggZZAll.root
   # S8=Trees/SignalAll8TeV.root
   # B8=Trees/BackgroundAll8TeV.root
   # Z8=OldTrees/HZZEventFitFormat_MC_ZJets_8TeV.root
   # G8=OldTrees/HZZEventFitFormat_ggZZAll.root

   S7=SyncTrees/SyncToys_7TeV_SMSignal.root
   B7=SyncTrees/SyncToys_7TeV_Bkg.root
   Z7=SyncTrees/SyncToys_7TeV_Bkg.root
   G7=SyncTrees/SyncToys_7TeV_Bkg.root
   S8=SyncTrees/SyncToys_8TeV_SMSignal.root
   B8=SyncTrees/SyncToys_8TeV_Bkg.root
   Z8=SyncTrees/SyncToys_8TeV_Bkg.root
   G8=SyncTrees/SyncToys_8TeV_Bkg.root

   time ./PerformFitsMixedZX $S7 $B7 $Z7 $G7 $S8 $B8 $Z8 $G8 $A2 $A3 0 0 0 0 $AL -1
   mv OutputFile.root $BaseDir/BatchResult/SMResult_${ID1}_${ID2}.root

fi

