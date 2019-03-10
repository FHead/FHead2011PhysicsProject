#!/bin/sh

AK4CHS=/eos/cms/store/group/phys_jetmet/magda/AK4chs_PU_GT/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/PU2017/180306_134748/*/*root
AK4CHSMe=/eos/cms/store/group/phys_heavyions/chenyi/MCTruth/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/RunIIFall17DRStdmix-FlatPU0to70_94X_mc2017_realistic_v10-v1/AODSIM/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/MCTruth2017WithPU/180525_193528/*/*root
PuppiPremix=/eos/cms/store/group/phys_jetmet/magda/Premixed_PU_puppi/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/akpuppi2017_premixed_pu/180507_163046/*/*root
PuppiFlat=/eos/cms/store/group/phys_jetmet/magda/WithPU_puppi/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/akpuppi2017_no_pu/180514_085504/*/*root
OutputBase=/eos/cms/store/cmst3/user/chenyi//BatchOutput/JetEnergyCorrection/MCTruthStudies/17434_SanityClosure

# Large rho from Andrew (May 23, 2018)
Input=$AK4CHSMe
Output=$OutputBase
L1=bias2SelectionPow_20180523_25nsV1_MC_L1FastJet_AK4PFchs_bigrho.txt
L2L3=Fall17_17Nov2017_V8_MC_L2Relative_AK4PFchs.txt
Tree="ak4pfchs/t"

# Premix, L1 with deriveL1 (Magda, May 28, 2018)
# Input=$PuppiPremix
# Output=$OutputBase/PuppiPremixDeriveL1
# L1=L1L2L3_PremixedPU_L1_deriveL1_ParallelMC_L1FastJet_AK4PUPPI.txt
# L2L3=L1L2L3_PremixedPU_L1_deriveL1_ParallelMC_L2Relative_AK4PUPPI.txt
# Tree="ak4puppi/t"

# Premix, L1+L2L3 with puppi function (Magda, May 28, 2018)
# Input=$PuppiPremix
# Output=$OutputBase/PuppiPremixPuppi
# L1=L1L2L3_PremixedPU_L1_jetsynchfit_puppi_ParallelMC_L1FastJet_AK4PUPPI.txt
# L2L3=L1L2L3_PremixedPU_L1_jetsynchfit_puppi_ParallelMC_L2Relative_AK4PUPPI.txt
# Tree="ak4puppi/t"

# Premix, L1+L2L3 with standard function (Magda, May 28, 2018)
# Input=$PuppiPremix
# Output=$OutputBase/PuppiPremixStandard
# L1=L1L2L3_PremixedPU_L1_jetsynchfit_standard_ParallelMC_L1FastJet_AK4PUPPI.txt
# L2L3=L1L2L3_PremixedPU_L1_jetsynchfit_standard_ParallelMC_L2Relative_AK4PUPPI.txt
# Tree="ak4puppi/t"

# Premix, L2L3 only (Magda, May 28, 2018)
# Input=$PuppiPremix
# Output=$OutputBase/PuppiPremixL2L3Only
# L1=Flat.txt
# L2L3=L2L3_PremixedPU_ParallelMC_L2Relative_AK4PUPPI.txt
# Tree="ak4puppi/t"

# Flat, L1+L2L3 with deriveL1 (Magda, May 28, 2018)
# Input=$PuppiFlat
# Output=$OutputBase/PuppiFlatDeriveL1
# L1=L1L2L3_FlatPU_L1_deriveL1_ParallelMC_L1FastJet_AK4PUPPI.txt
# L2L3=L1L2L3_FlatPU_L1_deriveL1_ParallelMC_L2Relative_AK4PUPPI.txt
# Tree="ak4puppi/t"

# Flat, L1+L2L3 with standard function (Magda, May 28, 2018)
# Input=$PuppiFlat
# Output=$OutputBase/PuppiFlatStandard
# L1=L1L2L3_FlatPU_L1_jetsynchfit_standard_ParallelMC_L1FastJet_AK4PUPPI.txt
# L2L3=L1L2L3_FlatPU_L1_jetsynchfit_standard_ParallelMC_L2Relative_AK4PUPPI.txt
# Tree="ak4puppi/t"

# Flat, L2L3 only (Magda, May 28, 2018)
# Input=$PuppiFlat
# Output=$OutputBase/PuppiFlatL2L3Only
# L1=Flat.txt
# L2L3=L2L3_FlatPU_ParallelMC_L2Relative_AK4PUPPI.txt
# Tree="ak4puppi/t"

# Debugging for Sifu on AK4PFchs, Mar+Mar
# Input=$AK4CHSMe
# Output=$OutputBase/SifuDebug17374MarMar
# L1=2017march5_closure_Fall17_25nsV1c_MC_L1FastJet_AK4PFchs.txt
# L2L3=2017march5_closure_Fall17_25nsV1c_MC_L2Relative_AK4PFchs.txt
# Tree="ak4pfchs/t"

# Mar+May
# Input=$AK4CHSMe
# Output=$OutputBase/SifuDebug17374MarMay
# L1=2017march5_closure_Fall17_25nsV1c_MC_L1FastJet_AK4PFchs.txt
# L2L3=2017may31_nonclosure_Fall17_25nsV1_MC_L2Relative_AK4PFchs.txt
# Tree="ak4pfchs/t"

# Debugging for Sifu on AK4PFchs, May+Mar
# Input=$AK4CHSMe
# Output=$OutputBase/SifuDebug17374MayMar
# L1=2017may31_nonclosure_Fall17_25nsV1_MC_L1FastJet_AK4PFchs.txt
# L2L3=2017march5_closure_Fall17_25nsV1c_MC_L2Relative_AK4PFchs.txt
# Tree="ak4pfchs/t"

# May+May
# Input=$AK4CHSMe
# Output=$OutputBase/SifuDebug17374MayMay
# L1=2017may31_nonclosure_Fall17_25nsV1_MC_L1FastJet_AK4PFchs.txt
# L2L3=2017may31_nonclosure_Fall17_25nsV1_MC_L2Relative_AK4PFchs.txt
# Tree="ak4pfchs/t"

mkdir -p $Output

Count=0
for i in `ls $Input | Reformat 20 | tr ' ' ':'`
do
   echo $i
   File=`echo $i | tr ':' ' '`
   cat RunFile.sh \
      | sed "s#__FILE__#$File#g" \
      | sed "s#__ID__#$Count#g" \
      | sed "s#__WORKDIR__#`pwd`#g" \
      | sed "s#__OUTPUT__#$Output#" \
      | sed "s#__L1__#$L1#g" \
      | sed "s#__L2L3__#$L2L3#g" \
      | sed "s#__TREE__#$Tree#g" \
      | bsub -J Transcribe
   Count=`echo $Count | AddConst 1`
done

