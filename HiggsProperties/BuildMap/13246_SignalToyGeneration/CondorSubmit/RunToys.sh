#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_6_0_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/BuildMap/13246_SignalToyGeneration

echo $HOSTNAME
echo "Current PWD = `pwd`"
echo "Home environment variable = $HOME"

WorkDir=`pwd`

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

cp -r $BaseDir/*cpp $WorkDir/
cp -r $BaseDir/*h $WorkDir/

sh compile.sh

time ./Run8TeV 125.6 $1 | ./ConvertToTree
mv ResultTree.root $BaseDir/CondorSubmit/Result/ResultTree_$1.root

