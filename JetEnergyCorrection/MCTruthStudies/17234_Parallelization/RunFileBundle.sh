#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17234_Parallelization/

__NOPUFILE__
__PUFILE__

echo Current directory content
ls
echo

jet_synchtest_x -samplePU `pwd`/PUFile.root -sampleNoPU `pwd`/NoPUFile.root -algo1 ak4pfchs -algo2 ak4pfchs -basepath '//'

mv output_ak4pfchs.root $WorkDir/Result/Result___ID__.root

