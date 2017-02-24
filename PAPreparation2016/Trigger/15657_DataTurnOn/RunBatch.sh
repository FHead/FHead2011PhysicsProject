#!/bin/sh --login

#BSUB -q 1nh

Type=__TYPE__
Run=__RUN__
Location=__INPUT__

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/PAPreparation2016/Trigger/15657_DataTurnOn

cmsStage $Location Input.root

$WorkDir/a.out Input.root Output.root
mv Output.root $WorkDir/Result/__OUTPUT__



