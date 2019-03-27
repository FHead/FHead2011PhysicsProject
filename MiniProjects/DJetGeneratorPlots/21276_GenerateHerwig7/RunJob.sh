#!/bin/bash

WorkDir=~/work/PhysicsWorkspace/MiniProjects/DJetGeneratorPlots/21276_GenerateHerwig7

export SCRAM_ARCH=slc6_amd64_gcc700
cd ~/work/CMSSW/CMSSW_10_3_2/src
eval `scramv1 runtime -sh`
cd - > /dev/null

Seed=`expr $2 + 10000`

sed "s/13579/$Seed/" < $WorkDir/RunHerwig.py > RunHerwig_${Seed}.py
cmsRun RunHerwig_${Seed}.py

rm InterfaceMatchboxTest*
rm HerwigConfig.in
rm chenyi.cc
rm RunHerwig_${Seed}.py

mv HiForestGEN.root $1



