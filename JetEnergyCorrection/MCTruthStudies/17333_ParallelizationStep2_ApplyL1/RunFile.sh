#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/

cp $WorkDir/*txt .
cp $WorkDir/My*PileupHistogram.root .

echo Input files are: __FILE__

hadd -k -f Input.root __FILE__

jet_apply_jec_x \
   -input Input.root \
   -output JRA_jecl1.root \
   -jecpath ./ \
   -era Parallelize_MC \
   -levels 1 \
   -algs ak4pfchs \
   -L1FastJet true \
   -saveitree false

cp $CMSSW_BASE/src/JetMETAnalysis/JetAnalyzers/config/jra_dr_finebinning.config jra.config

jet_response_analyzer_x jra.config \
   -input JRA_jecl1.root \
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
   -algs ak4pfchsl1 \
   -drmax 0.2 \
   -relrspmin 0.0 \
   -relrspmax 2.0

cp jra.root $WorkDir/MagdaWithPUAfterL1/JRA_jecl1___ID__.root

