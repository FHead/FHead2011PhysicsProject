#!/bin/sh --login

#BSUB -q 1nh

WorkDir=__WORKDIR__

source $WorkDir/Setup_CMSSW.sh

cp $WorkDir/Files/*txt .

echo Input files are: __FILE__

hadd -k -f Input.root __FILE__

jet_correction_analyzer_x \
   -inputFilename Input.root \
   -outputDir ./ \
   -path ./ \
   -era Fall17_17Nov2017_V20_MC \
   -levels "1,2" \
   -useweight true \
   -algs ak4pfchs \
   -drmax 0.2 \
   -evtmax 0 \
   -nbinsrelrsp 200 \
   -relrspmin 0.0 \
   -relrspmax 2.0 \
   -nrefmax 3

cp Closure_ak4pfchs.root __OUTPUT__/Closure_ak4pfchs___ID__.root

