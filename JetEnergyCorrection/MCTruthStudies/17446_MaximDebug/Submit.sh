
OutputBase=/eos/cms/store/group/phys_jetmet/chenyi/MCTruth/RunIIFall15MiniAODv2/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/MINIAODSIM/25nsNoPURaw_magnetOn_76X_mcRun2_asymptotic_v12-v1/Output2/
mkdir -p $OutputBase

Count=0
for i in `cat FileList`
do
   echo Current File = $i
   Count=`echo $Count | AddConst 1`
   cat RunJob.sh \
      | sed "s#__WORKDIR__#$PWD#" \
      | sed "s#__INPUT__#$i#" \
      | sed "s#__OUTPUT__#$OutputBase/JRA_${Count}.root#" \
      | bsub -q 8nh -J Maxim
done
