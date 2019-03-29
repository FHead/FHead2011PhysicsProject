#!/bin/bash

WorkDir=~/work/PhysicsWorkspace/MiniProjects/DJetGeneratorPlots/21315_BatchGeneratePythia/

export SCRAM_ARCH=slc6_amd64_gcc700
cd ~/work/CMSSW/CMSSW_10_3_2/src
eval `scramv1 runtime -sh`
cd - > /dev/null

cp $WorkDir/RunPythia.py RunPythia_Job.py
cmsRun RunPythia_Job.py

rm chenyi.cc
rm RunPythia_Job.py

cp $WorkDir/ExecuteSkim .

./ExecuteSkim --Input HiForestGEN.root --Output Skim.root --JetPTMin 30

mv Skim.root $1

rm HiForestGEN.root
rm ExecuteSkim

