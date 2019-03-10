#!/bin/bash

source Setup.sh

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/CommonCode/Proxy/x509up_proxy

cmsDriver.py step1 --filein $InputFile --fileout file:JME-RunIIAutumn18DR-00002_step1.root --mc --eventcontent RAWSIM --pileup NoPileUp --datatier GEN-SIM-RAW --conditions 102X_upgrade2018_realistic_v15 --step DIGI,L1,DIGI2RAW,HLT:@relval2018 --nThreads 8 --geometry DB:Extended --era Run2_2018 --python_filename JME-RunIIAutumn18DR-00002_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n $EventCount || exit $? ;
cmsRun -e -j JME-RunIIAutumn18DR-00002_rt.xml JME-RunIIAutumn18DR-00002_1_cfg.py || exit $? ; 

cmsDriver.py step2 --filein file:JME-RunIIAutumn18DR-00002_step1.root --fileout file:JME-RunIIAutumn18DR-00002.root --mc --eventcontent RECOSIM --runUnscheduled --datatier RECOSIM --conditions 102X_upgrade2018_realistic_v15 --step RAW2DIGI,L1Reco,RECO,RECOSIM,EI --nThreads 8 --geometry DB:Extended --era Run2_2018 --python_filename JME-RunIIAutumn18DR-00002_2_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n $EventCount || exit $? ;
cmsRun -e -j JME-RunIIAutumn18DR-00002_2_rt.xml JME-RunIIAutumn18DR-00002_2_cfg.py || exit $? ; 


