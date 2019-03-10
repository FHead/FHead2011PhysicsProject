#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17244_L1Correction/

cp $WorkDir/*txt .

jet_apply_jec_x -input $WorkDir/SimplePU/__FILE__ -era Simple -jecpath ./ -levels 1 -output $WorkDir/SimplePUAfterL1/__FILE__ -L1FastJet true




