#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_7_1_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/BuildMap/15265_UniformToy/
WorkDir=`pwd`

Seed=`echo $1 | awk '{print $1+10000}'`

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

# ln -s $BaseDir/*.cpp .
# ln -s $BaseDir/*.h .
ln -s $BaseDir/*.dat .
# ln -s $BaseDir/*.sh .

# sh compile.sh
cp $BaseDir/Run .

echo Starting to run!

./Run 125 13 $Seed > Result_13TeV_$Seed

grep EVENT Result_13TeV_$Seed | cut --delim=' ' --field=2- | TextToTree Meow_$Seed.root 17 "L1PT:L1Eta:L1Phi:L1ID:L2PT:L2Eta:L2Phi:L2ID:L3PT:L3Eta:L3Phi:L3ID:L4PT:L4Eta:L4Phi:L4ID:W"

cp Meow_$Seed.root $BaseDir/CondorSubmit/Result/





