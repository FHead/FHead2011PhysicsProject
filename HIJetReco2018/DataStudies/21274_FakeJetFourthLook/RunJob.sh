#!/bin/bash

Input=$1
Output=$2

export SCRAM_ARCH=slc6_amd64_gcc700
cd ~/work/CMSSW/CMSSW_10_3_1/src
eval `scramv1 runtime -sh`
cd - > /dev/null

ln -s /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias0/HIRun2018A-PromptReco-v2/AOD/HIMinimumBias0/HIMinimumBiasForest/190313_110718/ MB
cp ~/work/PhysicsWorkspace/HIJetReco2018/DataStudies/21274_FakeJetFourthLook/Execute Execute

./Execute --Input $1 --Output Output.root
mv Output.root $2




