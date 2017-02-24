#!/bin/sh --login

#BSUB -q 1nd

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

cmsStage /store/group/cmst3/group/hintt/mverweij/CS/MC/PbPb/Pythia6_Dijet220_pp502_Hydjet_MB/crab_HiForestDijet220P6V2/160708_164816/merge/HiForest_0.root Input0.root
cmsStage /store/group/cmst3/group/hintt/mverweij/CS/MC/PbPb/Pythia6_Dijet220_pp502_Hydjet_MB/crab_HiForestDijet220P6V2/160708_164816/merge/HiForest_1.root Input1.root

ls

/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetMass/JetStudies/15743_CS/RunCheckPartIV Input0.root Output_HiForest_0.root

cp Output_HiForest_0.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetMass/JetStudies/15743_CS

ls

/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetMass/JetStudies/15743_CS/RunCheckPartIV Input1.root Output_HiForest_1.root

cp Output_HiForest_1.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetMass/JetStudies/15743_CS


