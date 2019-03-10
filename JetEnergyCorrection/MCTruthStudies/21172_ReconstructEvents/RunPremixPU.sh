#!/bin/bash

source Setup.sh

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/CommonCode/Proxy/x509up_proxy

cmsDriver.py step1 --filein $InputFile --fileout file:JME-RunIIAutumn18DRPremix-00005_step1.root  --pileup_input "dbs:/Neutrino_E-10_gun/RunIISummer17PrePremix-PUAutumn18_102X_upgrade2018_realistic_v15-v1/GEN-SIM-DIGI-RAW" --mc --eventcontent PREMIXRAW --datatier GEN-SIM-RAW --conditions 102X_upgrade2018_realistic_v15 --step DIGI,DATAMIX,L1,DIGI2RAW,HLT:@relval2018 --procModifiers premix_stage2 --nThreads 8 --geometry DB:Extended --datamix PreMix --era Run2_2018 --python_filename JME-RunIIAutumn18DRPremix-00005_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n $EventCount || exit $? ; 
cmsRun -e -j JME-RunIIAutumn18DRPremix-00005_rt.xml JME-RunIIAutumn18DRPremix-00005_1_cfg.py || exit $? ; 

cmsDriver.py step2 --filein file:JME-RunIIAutumn18DRPremix-00005_step1.root --fileout file:JME-RunIIAutumn18DRPremix-00005.root --mc --eventcontent RECOSIM --runUnscheduled --datatier RECOSIM --conditions 102X_upgrade2018_realistic_v15 --step RAW2DIGI,L1Reco,RECO,RECOSIM,EI --procModifiers premix_stage2 --nThreads 8 --era Run2_2018 --python_filename JME-RunIIAutumn18DRPremix-00005_2_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n $EventCount || exit $? ; 
cmsRun -e -j JME-RunIIAutumn18DRPremix-00005_2_rt.xml JME-RunIIAutumn18DRPremix-00005_2_cfg.py || exit $? ; 

