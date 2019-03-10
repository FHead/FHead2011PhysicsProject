#!/bin/sh --login

#BSUB -q 1nh

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/

cp $WorkDir/*txt .
cp $WorkDir/My*PileupHistogram.root .

echo Input files are: /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_1.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_10.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_100.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_101.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_102.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_103.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_104.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_105.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_106.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_107.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_108.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_109.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_11.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_110.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_111.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_112.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_113.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_114.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_115.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_116.root

hadd -k -f Input.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_1.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_10.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_100.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_101.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_102.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_103.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_104.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_105.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_106.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_107.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_108.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_109.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_11.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_110.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_111.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_112.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_113.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_114.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_115.root /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/MCTruthStudies/17333_ParallelizationStep3_Closure/MagdaWithPU/0000/JRA_116.root

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

cp Closure_ak4pfchs.root $WorkDir/MagdaWithPUForClosure/Closure_ak4pfchs_0.root

