#!/bin/bash

WorkDir=~/work/PhysicsWorkspace/MiniProjects/DJetGeneratorPlots/21314_BatchGeneratePythiaWeighted/

export SCRAM_ARCH=slc6_amd64_gcc700
cd ~/work/CMSSW/CMSSW_10_3_2/src
eval `scramv1 runtime -sh`
cd - > /dev/null

cp $WorkDir/RunPythia.py RunPythia_Job.py
cmsRun RunPythia_Job.py

rm chenyi.cc
rm RunPythia_Job.py

mv HiForestGEN.root ${1/.root/_GEN.root}

rm HiForestGEN.root

