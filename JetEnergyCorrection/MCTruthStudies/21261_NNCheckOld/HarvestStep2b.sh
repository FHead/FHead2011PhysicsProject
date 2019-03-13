#!/bin/sh

source Setup_FileLocation.sh

hadd -k -f /tmp/chenyi/output_ak4pfchs.root $Step2bOutput/Result_*root
cp /tmp/chenyi/output_ak4pfchs.root $Step2bOutput/

mkdir -p SynchPlotStep2
mkdir -p SynchPlotStep2b

jet_synchplot_x \
   -inputDir $Step2Output \
   -algo1 ak4pfchs \
   -algo2 ak4pfchs \
   -outDir `pwd`/SynchPlotStep2 \
   -outputFormat .png \
   -fixedRange true \
   -tdr true \
   -npvRhoNpuBinWidth 10 \
   -NBinsNpvRhoNpu 6

jet_synchplot_x \
   -inputDir $Step2bOutput \
   -algo1 ak4pfchs \
   -algo2 ak4pfchs \
   -outDir `pwd`/SynchPlotStep2b \
   -outputFormat .png \
   -fixedRange true \
   -tdr true \
   -npvRhoNpuBinWidth 10 \
   -NBinsNpvRhoNpu 6

tar zcvf SynchPlot.tar.gz SynchPlotStep2/ SynchPlotStep2b/
cp SynchPlot.tar.gz ~/public/html/

