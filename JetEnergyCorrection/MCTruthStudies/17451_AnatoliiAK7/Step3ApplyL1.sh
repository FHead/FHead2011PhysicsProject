#!/bin/sh --login

#BSUB -q 1nh

WorkDir=__WORKDIR__

source $WorkDir/Setup_CMSSW.sh

cp $WorkDir/Files/*txt .
cp $WorkDir/Files/My*PileupHistogram.root .

echo Input files are: __FILE__

hadd -k -f Input.root __FILE__

# jet_apply_jec_x \
#    -input Input.root \
#    -output JRA_jecl1.root \
#    -jecpath ./ \
#    -era 2017may31_nonclosure_Fall17_25nsV1_MC \
#    -levels 1 \
#    -algs ak4pfchs \
#    -L1FastJet true \
#    -saveitree false

cp $CMSSW_BASE/src/JetMETAnalysis/JetAnalyzers/config/jra_dr_finebinning.config jra.config

jet_response_analyzer_y jra.config \
   -input Input.root \
   -nbinsabsrsp 0 \
   -nbinsetarsp 0 \
   -nbinsphirsp 0 \
   -nbinsrelrsp 200 \
   -doflavor false \
   -flavorDefinition phys \
   -output jra.root \
   -useweight true \
   -nrefmax 3 \
   -algs ak7pf \
   -drmax 0.2 \
   -relrspmin 0.0 \
   -relrspmax 2.0

cp jra.root __OUTPUT__/JRA_jecl1___ID__.root

