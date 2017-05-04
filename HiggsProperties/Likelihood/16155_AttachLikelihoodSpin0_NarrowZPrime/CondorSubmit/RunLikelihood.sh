#!/bin/sh
# source /cvmfs/cms.cern.ch/cmsset_default.sh
# cd /home/yichen/CMSSW/CMSSW_7_1_1/src
export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"
cat /proc/sys/kernel/hostname

BaseDir=$PhysicsWorkspace/HiggsProperties/Likelihood/16155_AttachLikelihoodSpin0_NarrowZPrime/
WorkDir=`pwd`

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

ln -s $BaseDir/*cpp $WorkDir/
ln -s $BaseDir/*h $WorkDir/
ln -s $BaseDir/*dat $WorkDir/
ln -s $BaseDir/OriginalTrees* $WorkDir/
ln -s $BaseDir/AttachedTrees* $WorkDir/
ln -s $BaseDir/BranchCentral* $WorkDir/

# sh compile.sh

cp $BaseDir/RunSignal $WorkDir/
cp $BaseDir/RunBackground $WorkDir/

echo "Compilation ended, now the heavy I/O from/to hadoop starts"

Input=$1
Output=$2
Seed=$3
Energy=$4

# cp $1 Current.root
# cmsStage -f $1 Current.root
# eos root://eosuser.cern.ch cp $1 Current.root
cp /$1 Current.root

MAX=999999999

./RunSignal Current.root 0 $MAX $Seed $Energy | cut --delim=' ' --field=3- > LogS
head -1 LogS
./AttachBranch BranchCentralSignal LogS Current.root
# rm LogS

./RunBackground Current.root 0 $MAX $Seed $Energy | cut --delim=' ' --field=3- > LogB
head -1 LogB
./AttachBranch BranchCentralBackground LogB Current.root
# rm LogB

# mv Current.root $2
# cmsStage -f Current.root $2
# eos root://eosuser.cern.ch cp Current.root $2
mv Current.root /$2


