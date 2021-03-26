#!/bin/bash

WorkDir=$1
Input=$2
Output=$3
Year=$4

cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_10_3_4/src
eval `scramv1 runtime -sh`
cd -

cp $WorkDir/My*PileupHistogram.root .
cp $WorkDir/JECDatabase/*RAAV2*/*L2Relative*.txt .

rename Autumn18_HI_RAAV2_MC RAA2018 *
rename Spring18_ppRef5TeV_RAAV2_MC RAA2017 *

echo $1
echo $2
echo $3

jet_correction_analyzer_x \
   -inputFilename $Input \
   -outputDir ./ \
   -path ./ \
   -era RAA${Year} \
   -levels 2 \
   -useweight false \
   -algs ak1pf ak2pf ak3pf ak4pf ak5pf ak6pf ak7pf ak8pf ak9pf \
   -drmax 0.08 0.1 0.15 0.2 0.25 0.3 0.4 0.5 0.6 \
   -evtmax 0 \
   -nbinsrelrsp 200 \
   -relrspmin 0.0 \
   -relrspmax 2.0 \
   -MCPUReWeighting MyMCPileupHistogram.root \
   -DataPUReWeighting MyDataPileupHistogram.root \
   -nrefmax 3

mv Closure_ak1pf_ak2pf_ak3pf_ak4pf_ak5pf_ak6pf_ak7pf_ak8pf_ak9pf.root $Output

rm *txt
rm My*PileupHistogram.root
