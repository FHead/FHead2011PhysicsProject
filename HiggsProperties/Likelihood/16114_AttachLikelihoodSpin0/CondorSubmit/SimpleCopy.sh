#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_7_1_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"
cat /proc/sys/kernel/hostname

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/Likelihood/16114_AttachLikelihoodSpin0/
WorkDir=`pwd`

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

ln -s $BaseDir/*cpp $WorkDir/
ln -s $BaseDir/*h $WorkDir/
ln -s $BaseDir/*dat $WorkDir/
ln -s $BaseDir/OriginalTrees* $WorkDir/
ln -s $BaseDir/AttachedTrees* $WorkDir/
ln -s $BaseDir/BranchCentral* $WorkDir/

echo "Compilation ended, now the heavy I/O from/to hadoop starts"

Input=$1
Output=$2
Seed=$3
Energy=$4

ls $WorkDir

echo ACBDEFGHIJKL > $2




