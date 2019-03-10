#!/bin/sh --login

#BSUB -q 1nh

WorkDir=$1
NoPUFile=$2
PUFile=$3
Output=$4
ID=$5

source $WorkDir/Setup_CMSSW.sh

pwd

if [[ $NoPUFile != *":"* ]]; then
   cp $NoPUFile NoPUFile.root
else
   hadd -f -k NoPUFile.root `echo $NoPUFile | tr ':' ' '`
fi

if [[ $PUFile != *":"* ]]; then
   cp $PUFile PUFile.root
else
   hadd -f -k PUFile.root `echo $PUFile | tr ':' ' '`
fi

cp $WorkDir/Files/*PileupHistogram.root .

echo Current directory content
ls
echo

jet_synchtree_x \
   -basepath '//' \
   -samplePU `pwd`/PUFile.root \
   -sampleNoPU `pwd`/NoPUFile.root \
   -algo1 ak4pf \
   -algo2 ak4pf \
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
jet_synchtree_x \
   -basepath '//' \
   -samplePU `pwd`/PUFile.root \
   -sampleNoPU `pwd`/NoPUFile.root \
   -algo1 ak4calo \
   -algo2 ak4calo \
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

mv output_ak4pf.root ${Output}/Result_PF_${ID}.root
mv output_ak4calo.root ${Output}/Result_Calo_${ID}.root

rm *.root
rm *.cc
