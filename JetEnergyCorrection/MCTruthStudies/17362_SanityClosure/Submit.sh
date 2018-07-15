#!/bin/sh

Input=/eos/cms/store/group/phys_jetmet/magda/AK4chs_PU_GT/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/PU2017/180306_134748/*/*root
Output=/eos/cms/store/cmst3/user/chenyi//BatchOutput/JetEnergyCorrection/MCTruthStudies/17362_SanityClosure/

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
      | bsub -J Transcribe
   Count=`echo $Count | AddConst 1`
done

