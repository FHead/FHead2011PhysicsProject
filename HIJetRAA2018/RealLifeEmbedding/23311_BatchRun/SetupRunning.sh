#!/bin/bash

InputDirectory=/eos/user/c/chenyi//JetSamples/23275_JetMorph/PTHat100HardQGP/
OutputDirectory=/eos/user/c/chenyi//BatchOutput/PhysicsWorkspace/HIJetRAA2018/RealLifeEmbedding/23311_BatchRun/PTHat100HardQGP/
Offset=10000 # 10000 for PTHat 100, 25000 for PTHat 250

Condor=Submit.condor

mkdir -p Log

rm -f $Condor
touch $Condor

echo "Universe              = vanilla" >> $Condor
echo "Executable            = $PWD/RunAll.sh" >> $Condor
echo "should_transfer_files = NO" >> $Condor
echo "+JobFlavour           = \"workday\"" >> $Condor
echo >> $Condor

for i in Morphed100HardQGP
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


