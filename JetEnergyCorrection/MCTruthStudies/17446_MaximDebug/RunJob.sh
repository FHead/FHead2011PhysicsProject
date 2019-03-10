#!/bin/bash

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

export X509_USER_PROXY=__WORKDIR__/x509up_proxy

cat __WORKDIR__/Config2.py | sed "s#__INPUTFILE__#__INPUT__#" > Config.py
cmsRun Config.py

cp JRA.root __OUTPUT__



