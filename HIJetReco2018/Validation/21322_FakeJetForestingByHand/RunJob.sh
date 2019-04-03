#!/bin/bash

Input=$1

export SCRAM_ARCH=slc6_amd64_gcc700
cd ~/work/CMSSW/CMSSW_10_3_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

export X509_USER_PROXY=~/work/PhysicsWorkspace/HIJetReco2018/CommonCode/proxy/x509up_proxy

WorkDir=~/work/PhysicsWorkspace/HIJetReco2018/Validation/21322_FakeJetForestingByHand/

cat $WorkDir/runForestAOD_pponAA_DATA_103X.py \
   | sed "s#__FILE__#$Input#" > Run.py

cmsRun Run.py
mv HiForestAOD.root $WorkDir/CondorOutput/`basename $Input`

rm Run.py



