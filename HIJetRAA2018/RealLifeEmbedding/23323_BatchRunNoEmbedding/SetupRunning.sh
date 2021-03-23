#!/bin/bash

InputDirectory=/eos/user/c/chenyi//JetSamples/23275_JetMorph/PTHat250/
OutputDirectory=/eos/user/c/chenyi//BatchOutput/PhysicsWorkspace/HIJetRAA2018/RealLifeEmbedding/23323_BatchRunNoEmbedding/PTHat250/

Condor=Submit.condor

mkdir -p Log

rm -f $Condor
touch $Condor

echo "Universe              = vanilla" >> $Condor
echo "Executable            = $PWD/RunAll.sh" >> $Condor
echo "should_transfer_files = NO" >> $Condor
echo "+JobFlavour           = \"longlunch\"" >> $Condor
echo >> $Condor

for i in Original Morphed
do
   for j in `seq 1 100`
   do
      Seed=`echo $j | AddConst $Offset`

      echo "Arguments = $InputDirectory/${i}_${j}.hepmc $OutputDirectory/${i}_${j}.root $PWD $Seed" >> $Condor
      echo "Output    = Log/${i}_${j}.out" >> $Condor
      echo "Error     = Log/${i}_${j}.err" >> $Condor
      echo "Log       = Log/${i}_${j}.log" >> $Condor
      echo "Queue" >> $Condor
      echo >> $Condor
   done
done


