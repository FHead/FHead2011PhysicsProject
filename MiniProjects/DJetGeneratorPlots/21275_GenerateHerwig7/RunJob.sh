#!/bin/bash

WorkDir=~/work/PhysicsWorkspace/MiniProjects/DJetGeneratorPlots/21275_GenerateHerwig7

export SCRAM_ARCH=slc6_amd64_gcc700
cd ~/work/CMSSW/CMSSW_10_3_2/src
eval `scramv1 runtime -sh`
cd - > /dev/null

sed "s/13579/$2/" < $WorkDir/RunHerwig.py > RunHerwig.py
cmsRun RunHerwig.py

rm InterfaceMatchboxTest*
rm HerwigConfig.in
rm chenyi.cc

mv HiForestGEN.root $1



