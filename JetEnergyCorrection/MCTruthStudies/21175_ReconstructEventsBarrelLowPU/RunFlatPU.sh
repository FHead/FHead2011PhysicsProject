#!/bin/bash

RandomSeed=$1
WorkDir=$2

source Setup.sh

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/CommonCode/Proxy/x509up_proxy

# cmsDriver.py step1 --filein file:pickevents.root --fileout file:JME-RunIIAutumn18DR-00003_step1.root --pileup_input "dbs:/MinBias_TuneCP5_13TeV-pythia8/RunIIFall18GS-102X_upgrade2018_realistic_v9-v1/GEN-SIM" --mc --eventcontent RAWSIM --pileup Flat_10_50_25ns --datatier GEN-SIM-RAW --conditions 102X_upgrade2018_realistic_v15 --customise_commands "process.mix.input.nbPileupEvents.probFunctionVariable = cms.vint32(0,1,2,3,4) \n process.mix.input.nbPileupEvents.probValue = cms.vdouble(0.200000,0.200000,0.200000,0.200000,0.200000)" --step DIGI,L1,DIGI2RAW,HLT:@relval2018 --nThreads 8 --geometry DB:Extended --era Run2_2018 --python_filename JME-RunIIAutumn18DR-00003_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 20

sed "s/__RANDOM__/$RandomSeed/g" < $WorkDir/JME-RunIIAutumn18DR-00003_1_cfg.py > JME-RunIIAutumn18DR-00003_1_cfg.py
cmsRun -e -j JME-RunIIAutumn18DR-00003_rt.xml JME-RunIIAutumn18DR-00003_1_cfg.py || exit $? ; 

# cmsDriver.py step2 --filein file:JME-RunIIAutumn18DR-00003_step1.root --fileout file:JME-RunIIAutumn18DR-00003.root --mc --eventcontent RECOSIM --runUnscheduled --datatier RECOSIM --conditions 102X_upgrade2018_realistic_v15 --step RAW2DIGI,L1Reco,RECO,RECOSIM,EI --nThreads 8 --geometry DB:Extended --era Run2_2018 --python_filename JME-RunIIAutumn18DR-00003_2_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n $EventCount || exit $? ; 

cp $WorkDir/JME-RunIIAutumn18DR-00003_2_cfg.py .
cmsRun -e -j JME-RunIIAutumn18DR-00003_2_rt.xml JME-RunIIAutumn18DR-00003_2_cfg.py || exit $? ; 


