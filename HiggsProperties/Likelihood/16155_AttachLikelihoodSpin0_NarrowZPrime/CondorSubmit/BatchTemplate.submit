#!/bin/sh --login

#BSUB -q 1nd

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

cp /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HiggsProperties/Likelihood/16155_AttachLikelihoodSpin0_NarrowZPrime/CondorSubmit/RunLikelihood.sh Run.sh
sh Run.sh __INPUT__ __OUTPUT__ __SEED__ __ENERGY__

