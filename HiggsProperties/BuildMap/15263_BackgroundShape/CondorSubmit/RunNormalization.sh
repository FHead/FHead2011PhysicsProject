#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_7_1_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/BuildMap/15263_BackgroundShape/
WorkDir=`pwd`

Seed=`echo $1 | awk '{print $1+100000}'`

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

# ln -s $BaseDir/*.cpp .
# ln -s $BaseDir/*.h .
ln -s $BaseDir/*.dat .
# ln -s $BaseDir/*.sh .

# sh compile.sh
cp $BaseDir/Run .

./Run 125 13 $Seed > Result_13TeV_$Seed

grep EVENT Result_13TeV_$Seed | cut --delim=' ' --field=2- | TextToTree Meow_$Seed.root 42 "P1X:P1Y:P1Z:P2X:P2Y:P2Z:P3X:P3Y:P3Z:P4X:P4Y:P4Z:EMUU:EMDD:EEUU:EEDD:EMA:EMB:EMC:EMD:EME:EMF:EMG:EMH:EMI:EMJ:EMK:EML:EMM:EEA:EEB:EEC:EED:EEE:EEF:EEG:EEH:EEI:EEJ:EEK:EEL:EEM"
# grep EVENT Result_13TeV_$Seed | cut --delim=' ' --field=2-17 | TextToTree MeowSimple_$Seed.root 16 "P1X:P1Y:P1Z:P2X:P2Y:P2Z:P3X:P3Y:P3Z:P4X:P4Y:P4Z:EMUU:EMDD:EEUU:EEDD"

mv Meow_$Seed.root $BaseDir/CondorSubmit/Result/
# mv MeowSimple_$Seed.root $BaseDir/CondorSubmit/Result/




