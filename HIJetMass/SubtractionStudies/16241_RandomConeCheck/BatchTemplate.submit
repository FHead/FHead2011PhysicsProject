#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

cmsStage __INPUT__ Input.root






__EXECUTABLE__ Input.root Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ __EXTRA1__ __EXTRA2__ __EXTRA3__ 
# cmsStage Output.root /store/cmst3/user/chenyi/BatchOutput/HIJetMass/SubtractionStudies/16241_RandomConeCheck//Result/`basename __OUTPUT__`
mv Output.root __OUTPUT__
