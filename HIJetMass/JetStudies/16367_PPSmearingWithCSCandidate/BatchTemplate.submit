#!/bin/sh --login

#BSUB -q 1nw
#BSUB -F 60000000

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

if [[ __INPUT__ != root* ]]
then
   # cmsStage __INPUT__ Input.root
   eos cp /eos/cms/__INPUT__ Input.root
fi

eos cp /eos/cms/store/cmst3/user/chenyi/Samples/CymbalMB/HiForestAOD_89.root MBInput.root
# cmsStage /store/cmst3/user/chenyi/Samples/CymbalMB/HiForestAOD_79.root MBInput.root

# eos cp /eos/cms/store/cmst3/user/chenyi/Samples/HIMinimumBias2/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1/160311_153742/0000/HiForestAOD_100.root MBInput.root

export X509_USER_PROXY=$PhysicsWorkspace/HIJetMass/CommonCode/proxy/x509up_proxy


if [[ __INPUT__ != root* ]]
then
   __EXECUTABLE__ Input.root Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ MBInput.root 0.07 6.00 __EXTRA1__ __EXTRA2__ __EXTRA3__ 
else
   __EXECUTABLE__ __INPUT__ Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ MBInput.root 0.07 6.00 __EXTRA1__ __EXTRA2__ __EXTRA3__ 
fi

# __EXECUTABLE__ Input.root Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ root://xrootd.cmsaf.mit.edu//store/user/rbi/merged/HIMinimumBias2-HIRun2015-PromptReco-v1_forest_csjet_v1//0.root 0.07 1.20 __EXTRA1__ __EXTRA2__ __EXTRA3__ 

eos cp Output.root /eos/cms/store/cmst3/user/chenyi/BatchOutput/HIJetMass/JetStudies/16367_PPSmearingWithCSCandidate//Result/Mod__EXTRA2___`basename __OUTPUT__`
# mv Output.root __OUTPUT__

