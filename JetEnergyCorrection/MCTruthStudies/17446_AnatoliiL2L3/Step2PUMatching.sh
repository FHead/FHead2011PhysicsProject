#!/bin/sh --login

#BSUB -q 1nh

WorkDir=__WORKDIR__

source $WorkDir/Setup_CMSSW.sh

__NOPUFILE__
__PUFILE__
cp $WorkDir/Files/*PileupHistogram.root .

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

mv output_ak4pfchs.root __OUTPUT__/Result___ID__.root

