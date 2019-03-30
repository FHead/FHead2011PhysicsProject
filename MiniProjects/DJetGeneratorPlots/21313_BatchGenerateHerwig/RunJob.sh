#!/bin/bash

WorkDir=~/work/PhysicsWorkspace/MiniProjects/DJetGeneratorPlots/21313_BatchGenerateHerwig

export SCRAM_ARCH=slc6_amd64_gcc700
cd ~/work/CMSSW/CMSSW_10_3_2/src
eval `scramv1 runtime -sh`
cd - > /dev/null

Seed=`expr $2 + 20000`

sed "s/13579/$Seed/" < $WorkDir/RunHerwig.py > RunHerwig_${Seed}.py
cmsRun RunHerwig_${Seed}.py

rm InterfaceMatchboxTest*
rm HerwigConfig.in
rm chenyi.cc
rm RunHerwig_${Seed}.py

cp $WorkDir/ExecuteSkim .

./ExecuteSkim --Input HiForestGEN.root --Output Skim.root --JetPTMin 30

mv Skim.root $1
# mv HiForestGEN.root ${1/.root/_GEN.root}

rm HiForestGEN.root
rm ExecuteSkim

