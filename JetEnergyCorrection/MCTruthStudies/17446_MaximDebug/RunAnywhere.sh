#!/bin/bash

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17446_MaximDebug/x509up_proxy

cat /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17446_MaximDebug/Config2.py | sed "s#__INPUTFILE__#/store/mc/RunIIFall15MiniAODv2/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/25nsNoPURaw_magnetOn_76X_mcRun2_asymptotic_v12-v1/60000/FE2EDBA3-02C4-E511-A137-E41D2D08E070.root#" > Config.py
cmsRun Config.py

cp JRA.root /eos/cms/store/group/phys_jetmet/chenyi/MCTruth/RunIIFall15MiniAODv2/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/25nsNoPURaw_magnetOn_76X_mcRun2_asymptotic_v12-v1/Output2/Test.root



