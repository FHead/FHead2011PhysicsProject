#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/

cp $WorkDir/*txt .
cp $WorkDir/My*PileupHistogram.root .

echo Input files are: __FILE__

hadd -k -f Input.root __FILE__

jet_correction_analyzer_x \
   -inputFilename Input.root \
   -outputDir ./ \
   -path ./ \
   -era Parallelize_MC \
   -levels 1 2 \
   -useweight true \
   -algs ak4pfchs \
   -drmax 0.2 \
   -evtmax 0 \
   -nbinsrelrsp 200 \
   -relrspmin 0.0 \
   -relrspmax 2.0 \
   -MCPUReWeighting MyMCPileupHistogram.root \
   -DataPUReWeighting MyDataPileupHistogram.root \
   -nrefmax 3

cp Closure_ak4pfchs.root $WorkDir/MagdaWithPUForClosure/Closure_ak4pfchs___ID__.root

