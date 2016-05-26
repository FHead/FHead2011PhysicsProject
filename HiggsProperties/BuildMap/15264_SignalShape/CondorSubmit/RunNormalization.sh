#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_7_1_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/BuildMap/15264_SignalShape/
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

grep EVENT Result_13TeV_$Seed | cut --delim=' ' --field=2- | TextToTree Meow_$Seed.root 40 "EM:EE:P1X:P1Y:P1Z:P2X:P2Y:P2Z:P3X:P3Y:P3Z:P4X:P4Y:P4Z:EMA:EMB:EMC:EMD:EME:EMF:EMG:EMH:EMI:EMJ:EMK:EML:EMM:EEA:EEB:EEC:EED:EEE:EEF:EEG:EEH:EEI:EEJ:EEK:EEL:EEM"

cp Meow_$Seed.root $BaseDir/CondorSubmit/Result/





