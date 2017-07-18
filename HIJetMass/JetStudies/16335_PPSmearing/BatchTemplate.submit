#!/bin/sh --login

#BSUB -q 1nw
#BSUB -F 40000000

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

cmsStage __INPUT__ Input.root
cmsStage /store/cmst3/user/chenyi/Samples/CymbalMB/HiForestAOD_89.root MBInput.root
# cmsStage /store/cmst3/user/chenyi/Samples/HIMinimumBias2/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1/160311_153742/0000/HiForestAOD_100.root MBInput.root

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetMass/JetStudies/16335_PPSmearing/x509up_proxy


__EXECUTABLE__ Input.root Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ MBInput.root 0.07 6.00 __EXTRA1__ __EXTRA2__ __EXTRA3__ 
# __EXECUTABLE__ Input.root Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ root://xrootd.cmsaf.mit.edu//store/user/rbi/merged/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1//0.root 0.07 1.20 __EXTRA1__ __EXTRA2__ __EXTRA3__ 

cmsStage Output.root /store/cmst3/user/chenyi/BatchOutput/HIJetMass/JetStudies/16335_PPSmearing//Result/Mod__EXTRA2___`basename __OUTPUT__`
# mv Output.root __OUTPUT__

