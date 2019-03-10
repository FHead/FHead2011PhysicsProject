#!/bin/bash

source Setup.sh

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/CommonCode/Proxy/x509up_proxy

cmsDriver.py step1 --filein $InputFile --fileout file:JME-RunIIAutumn18DR-00003_step1.root --pileup_input "dbs:/MinBias_TuneCP5_13TeV-pythia8/RunIIFall18GS-102X_upgrade2018_realistic_v9-v1/GEN-SIM" --mc --eventcontent RAWSIM --pileup Flat_10_50_25ns --datatier GEN-SIM-RAW --conditions 102X_upgrade2018_realistic_v15 --customise_commands "process.mix.input.nbPileupEvents.probFunctionVariable = cms.vint32(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70) \n process.mix.input.nbPileupEvents.probValue = cms.vdouble(0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085,0.014085)" --step DIGI,L1,DIGI2RAW,HLT:@relval2018 --nThreads 1 --geometry DB:Extended --era Run2_2018 --python_filename JME-RunIIAutumn18DR-00003_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n $EventCount || exit $? ; 

cmsDriver.py step2 --filein file:JME-RunIIAutumn18DR-00003_step1.root --fileout file:JME-RunIIAutumn18DR-00003.root --mc --eventcontent RECOSIM --runUnscheduled --datatier RECOSIM --conditions 102X_upgrade2018_realistic_v15 --step RAW2DIGI,L1Reco,RECO,RECOSIM,EI --nThreads 8 --geometry DB:Extended --era Run2_2018 --python_filename JME-RunIIAutumn18DR-00003_2_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n $EventCount || exit $? ; 

Output=/afs/cern.ch/user/c/chenyi/EOSBox/Share/21172_ReconstructEvents//FlatPU/RunLocal/
mkdir -p $Output
for ID in `seq 0 9`
do
   cmsRun -e -j JME-RunIIAutumn18DR-00003_rt.xml JME-RunIIAutumn18DR-00003_1_cfg.py || exit $? ; 
   cmsRun -e -j JME-RunIIAutumn18DR-00003_2_rt.xml JME-RunIIAutumn18DR-00003_2_cfg.py || exit $? ;
   cp JME-RunIIAutumn18DR-00003_step1.root $Output/RunLocal/Step1Run${ID}.root
   cp JME-RunIIAutumn18DR-00003.root $Output/RunLocal/Step2Run${ID}.root
done




