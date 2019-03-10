#!/bin/bash

InputFile=$1
JRAFile=$2
NoPUJRAFile=$3
SynchFile=$4

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/21174_JRATreesCondorRun
JRATemplate=${WorkDir}/run_JRA_cfg.py

echo Input arguments
echo    InputFile   = $InputFile
echo    JRAFile     = $JRAFile
echo    NoPUJRAFile = $NoPUJRAFile
echo    SynchFile   = $SynchFile

[ -f "$InputFile" ] || echo "Input file not found!"

cp ${WorkDir}/Setup.sh .
source Setup.sh

cp $InputFile Input.root

sed "s#__FILE__#Input.root#g" < $JRATemplate > RunJRA.py
cmsRun RunJRA.py
rm RunJRA.py
cp JRA.root $JRAFile

jet_synchtree_x \
   -basepath '//' \
   -samplePU `pwd`/JRA.root \
   -sampleNoPU $NoPUJRAFile \
   -algo1 ak4pf \
   -algo2 ak4pf \
   -iftest false \
   -maxEvts 10000000 \
   -ApplyJEC false \
   -outputPath `pwd`/ \
   -npvRhoNpuBinWidth 10 \
   -NBinsNpvRhoNpu 6 \
   -useweight true \
   -nrefmax 3 \
   -doNotSave true

mv output_ak4pf.root $SynchFile

rm *root
rm *py
rm *sh
rm *cc

