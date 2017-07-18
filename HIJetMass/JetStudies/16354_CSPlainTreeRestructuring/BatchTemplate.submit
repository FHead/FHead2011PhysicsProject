#!/bin/sh --login

#BSUB -q 2nw

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

if [[ __INPUT__ != root* ]]
then
   eos cp /eos/cms/__INPUT__ Input.root
fi

export X509_USER_PROXY=$PhysicsWorkspace/HIJetMass/CommonCode/proxy/x509up_proxy

echo $X509_USER_PROXY



if [[ __INPUT__ != root* ]]
then
   __EXECUTABLE__ Input.root Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ __EXTRA1__ __EXTRA2__ __EXTRA3__ 
else
   __EXECUTABLE__ __INPUT__ Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ __EXTRA1__ __EXTRA2__ __EXTRA3__ 
fi

eos cp Output.root /eos/cms/store/cmst3/user/chenyi/BatchOutput/HIJetMass/JetStudies/16354_CSPlainTreeRestructuring//Result/`basename __OUTPUT__`
# mv Output.root __OUTPUT__
