#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/

cp $WorkDir/*txt .
cp $WorkDir/My*PileupHistogram.root .

echo Input files are: /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_1.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_10.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_100.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_101.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_102.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_103.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_104.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_105.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_106.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_107.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_108.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_109.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_11.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_110.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_111.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_112.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_113.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_114.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_115.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_116.root

hadd -k -f Input.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_1.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_10.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_100.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_101.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_102.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_103.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_104.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_105.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_106.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_107.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_108.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_109.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_11.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_110.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_111.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_112.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_113.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_114.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_115.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep2_ApplyL1/MagdaWithPU/0000/JRA_116.root

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

cp jra.root $WorkDir/MagdaWithPUAfterL1/JRA_jecl1_0.root

