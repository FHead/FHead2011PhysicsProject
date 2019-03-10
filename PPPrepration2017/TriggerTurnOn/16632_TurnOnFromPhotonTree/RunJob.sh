#!/bin/sh

SubmitDirectory=__HERE__

cd ~/work/CMSSW/CMSSW_9_2_12_patch1/src
eval `scramv1 runtime -sh`
cd - > /dev/null

export X509_USER_PROXY=~/work/PhysicsWorkspace/PPPrepration2017/CommonCode/proxy/x509up_proxy

ID=__ID__

sed "s/__JOB__/$ID/g" < $SubmitDirectory/MenuV10.py > Meow.py

cmsRun Meow.py

mv openHLT*root $SubmitDirectory/Result/



