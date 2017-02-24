#!/bin/sh --login

#BSUB -q 1nh

Type=__TYPE__
Run=__RUN__

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/PAPreparation2016/Trigger/15635_DataTurnOn


if [ "$Type" == "Data" ]
then
   cmsStage /store/group/phys_heavyions/kjung/ExpressForests/v6/000/${Run:0:3}/${Run:3:3}/__INPUT__ Input.root
elif [ "$Type" == "Streamer" ]
then
   cmsStage /store/group/phys_heavyions/kjung/StreamerForests/v2/000/${Run:0:3}/${Run:3:3}/__INPUT__ Input.root
fi

echo __INPUT__

$WorkDir/a.out Input.root Output.root
mv Output.root $WorkDir/Result/__OUTPUT__



