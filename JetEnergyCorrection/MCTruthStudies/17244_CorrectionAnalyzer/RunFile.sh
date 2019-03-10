#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17244_CorrectionAnalyzer/

cp $WorkDir/*txt .

jet_correction_analyzer_x -inputFilename $WorkDir/SimplePU/__FILE__ -outputDir ./ -path ./ -era Simple -levels "1 2 3" -algs ak4pfchs -drmax 0.2
mv Closure_ak4pfchs.root $WorkDir/Result/__FILE__



