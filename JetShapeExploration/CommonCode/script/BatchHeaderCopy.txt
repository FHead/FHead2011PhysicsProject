#!/bin/sh --login

#BSUB -q 8nh

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/CMSSW_7_5_8_patch3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

eos cp /eos/cms/__INPUT__ Input.root






