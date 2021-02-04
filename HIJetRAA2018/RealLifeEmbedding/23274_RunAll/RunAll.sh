#!/bin/bash

cd ~/work/CMSSW/CMSSW_10_3_5/src
eval `scramv1 runtime -sh`
cd - > /dev/null

HEPMC=$1
WORK=~/work/PhysicsWorkspace/HIJetRAA2018/RealLifeEmbedding/23274_RunAll

cp $HEPMC input.hepmc

cmsRun $WORK/Step1.py
cmsRun $WORK/Step2.py
cmsRun $WORK/Step3.py
cmsRun $WORK/Step4.py

