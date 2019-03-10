#!/bin/sh --login

#BSUB -q 1nd

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

# cmsStage __INPUT__ Input.root
# __EXECUTABLE__ Input.root Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ __EXTRA1__ __EXTRA2__ __EXTRA3__ 
# cmsStage -f Output.root /store/cmst3/user/chenyi/BatchOutput/HIJetMass/GeneratorStudies/16356_GenLevelJetMass//Result/`basename __OUTPUT__`
# mv Output.root __OUTPUT__

cp /eos/cms/__INPUT__ Input.root
__EXECUTABLE__ Input.root Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ __EXTRA1__ __EXTRA2__ __EXTRA3__ 
cp Output.root /eos/cms/store/cmst3/user/chenyi/BatchOutput/HIJetMass/GeneratorStudies/16356_GenLevelJetMass//Result/`basename __OUTPUT__`
