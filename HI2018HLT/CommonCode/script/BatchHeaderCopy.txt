#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

# if [[ __INPUT__ != root* ]]
# then
#    eos cp /eos/cms/__INPUT__ Input.root
# fi

export X509_USER_PROXY=$PhysicsWorkspace/HIJetMass/CommonCode/proxy/x509up_proxy
echo $X509_USER_PROXY






