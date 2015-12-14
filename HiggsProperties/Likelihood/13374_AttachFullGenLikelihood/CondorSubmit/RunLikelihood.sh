#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_6_0_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/Likelihood/13374_AttachFullGenLikelihood/
WorkDir=`pwd`

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

ln -s $BaseDir/*cpp $WorkDir/
ln -s $BaseDir/*h $WorkDir/
ln -s $BaseDir/OriginalTrees* $WorkDir/
ln -s $BaseDir/AttachedTrees* $WorkDir/
ln -s $BaseDir/BranchCentral* $WorkDir/

sh compile.sh

Input=$1
Output=$2

cp $1 Current.root

./RunSignal $1 0 99999999 | cut --delim=' ' --field=3- > LogS
head -5 LogS
./AttachBranch BranchCentralSignal LogS Current.root
rm LogS

./RunBackground $1 0 9999999 | cut --delim=' ' --field=3- > LogB
head -5 LogB
./AttachBranch BranchCentralBackground LogB Current.root
rm LogB

mv Current.root $2



