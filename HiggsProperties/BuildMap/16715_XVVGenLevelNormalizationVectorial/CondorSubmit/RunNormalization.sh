#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_7_1_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/BuildMap/15123_GenLevelNormalizationSignalZAAZWithPDF/
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
./Run 125 14 $Seed > Result_14TeV_$Seed
./Run 125 0 $Seed > Result_0TeV_$Seed

bzip2 Result_*

cp Result_14TeV_${Seed}.bz2 $BaseDir/CondorSubmit/Result/
cp Result_13TeV_${Seed}.bz2 $BaseDir/CondorSubmit/Result/
cp Result_0TeV_${Seed}.bz2 $BaseDir/CondorSubmit/Result/





