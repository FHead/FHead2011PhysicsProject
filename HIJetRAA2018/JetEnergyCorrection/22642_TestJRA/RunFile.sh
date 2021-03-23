#!/bin/bash

WorkDir=$1
Input=$2
Output=$3

cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_10_3_4/src
eval `scramv1 runtime -sh`
cd -

cp $CMSSW_BASE/src/JetMETAnalysis/JetAnalyzers/config/jra_dr_finebinning.config jra.config
cp $WorkDir/My*PileupHistogram.root .

echo $1
echo $2
echo $3

jet_response_analyzer_x jra.config \
      -input $Input \
      -nbinsabsrsp 0 \
      -nbinsetarsp 0 \
      -nbinsphirsp 0 \
      -nbinsrelrsp 200 \
      -doflavor false \
      -flavorDefinition phys \
      -MCPUReWeighting MyMCPileupHistogram.root \
      -MCPUHistoName pileup \
      -DataPUReWeighting MyDataPileupHistogram.root \
      -DataPUHistoName pileup \
      -output jra.root \
      -useweight true \
      -nrefmax 3 \
      -algs ak1pf:0.08 ak2pf:0.1 ak3pf:0.15 ak4pf:0.2 ak5pf:0.25 ak6pf:0.3 ak7pf:0.4 ak8pf:0.5 ak9pf:0.6 \
      -drmax 0.2 \
      -relrspmin 0.0 \
      -relrspmax 2.0

mv jra.root $Output

rm jra.config
rm My*PileupHistogram.root
