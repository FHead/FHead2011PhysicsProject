#!/bin/sh --login

#BSUB -q 2nw

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

__EXECUTABLE__ 18.4 0 __RUNNUMBER__ > Result.txt

bzip2 Result.txt

mv Result.txt.bz2 __RESULT__

