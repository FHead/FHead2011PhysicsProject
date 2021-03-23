#!/bin/bash

cd ~/work/CMSSW/CMSSW_10_3_5/src
eval `scramv1 runtime -sh`
cd - > /dev/null

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetRAA2018/CommonCode/proxy/x509up_proxy

HEPMC=$1
Output=$2
WORK=$3

cp $HEPMC input.hepmc

cp $WORK/Step*.py .

cmsRun Step1.py
cmsRun Step2.py
cmsRun Step3.py
cmsRun Step4.py

mkdir -p `dirname $Output`
mv HiForestAOD.root $Output

rm *root
rm Step*py
rm input.hepmc
