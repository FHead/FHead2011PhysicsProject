#!/bin/sh --login

#BSUB -q 2nd

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

__EXECUTABLE__ 18.4 0 __RUNNUMBER__

# mv OutputFile.root __RESULT__
cmsStage OutputFile.root /store/cmst3/user/chenyi//BatchOutput/HiggsProperties/LightBosonStudies/16341_DistributionFromToy/Result/`basename __RESULT__`

