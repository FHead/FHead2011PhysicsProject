#!/bin/bash

WorkDir=$1
Input=$2
Output=$3

if [ -s "$Output" ]; then
   echo "File exists and nonzero, do nothing"
   exit
fi

echo "File is nonzero, or does not exist - run it"

cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_9_4_10/src
eval `scramv1 runtime -sh`
cd -

sed "s#__FILE__#$Input#g" < $WorkDir/runForestAOD_pp_MC_94X.py > RunCMSSW.py

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetRAA2018/CommonCode/proxy/x509up_proxy

cmsRun RunCMSSW.py

mv HiForestAOD.root $Output

rm RunCMSSW.py


