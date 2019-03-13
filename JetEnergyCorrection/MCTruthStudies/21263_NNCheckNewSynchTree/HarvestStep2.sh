#!/bin/sh

Function=MikkoSuggestion

source Setup_FileLocation.sh

mkdir -p $Step2Output/Temp/

hadd -k -f /tmp/chenyi/output_ak4pfchs.root $Step2Output/Result_*root
cp /tmp/chenyi/output_ak4pfchs.root $Step2Output
cp $Step2Output/output_ak4pfchs.root $Step2Output/Temp/output_ak4pfchs.root

jet_synchfit_x \
   -inputDir  $Step2Output/Temp \
   -outputDir `pwd`/Files/ \
   -algo1 ak4pfchs \
   -algo2 ak4pfchs \
   -highPU false \
   -useNPU false \
   -functionType $Function \
   -era ParallelMCPreDeriveL1 \
   -ScaleErrors true

mv Files/Parameter_ak4pfchs.root Files/Parameter_NoPTHatCut_ak4pfchs.root

