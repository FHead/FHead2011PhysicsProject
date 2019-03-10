#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17244_ResponseAnalyzer/

cp $WorkDir/*txt .

jet_response_analyzer_x $WorkDir/jra.config -input $WorkDir/SimplePUAfterL1/__FILE__ -output $WorkDir/ResponseAnalyzer/__FILE__




