#!/bin/sh --login

#BSUB -q 1nd

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17332_ParallelizationStep1_SynchTest/

__NOPUFILE__
__PUFILE__
cp $WorkDir/*PileupHistogram.root .

echo Current directory content
ls
echo

jet_synchtest_x \
   -basepath '//' \
   -samplePU `pwd`/PUFile.root \
   -sampleNoPU `pwd`/NoPUFile.root \
   -algo1 ak4pfchs \
   -algo2 ak4pfchs \
   -iftest false \
   -maxEvts 10000000 \
   -ApplyJEC false \
   -outputPath `pwd`/ \
   -npvRhoNpuBinWidth 10 \
   -NBinsNpvRhoNpu 6 \
   -MCPUReWeighting `pwd`/MyMCPileupHistogram.root \
   -DataPUReWeighting `pwd`/MyDataPileupHistogram.root \
   -useweight true \
   -nrefmax 3 \
   -doNotSave false

mv output_ak4pfchs.root $WorkDir/Result/Result___ID__.root

