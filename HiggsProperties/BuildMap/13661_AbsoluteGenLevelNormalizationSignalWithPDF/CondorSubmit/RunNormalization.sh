#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_6_0_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/BuildMap/13661_AbsoluteGenLevelNormalizationSignalWithPDF/
WorkDir=`pwd`

Seed=$1

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

ln -s $BaseDir/*.cpp .
ln -s $BaseDir/*.h .
ln -s $BaseDir/*.dat .
ln -s $BaseDir/*.sh .

sh compile.sh

./Run 125 $1 > Result_$1

cp Result_$1 $BaseDir/CondorSubmit/Result/





