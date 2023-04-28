#!/bin/bash

File=Submit.condor

rm -f $File

echo "Universe              = vanilla" >> $File
echo "Executable            = /afs/cern.ch/user/c/chenyi/PhysicsWorkspace/HI2022HLT/JetEnergyCorrection/25127_CustomJRATree/RunOnePair.sh" >> $File
echo "should_transfer_files = NO" >> $File
echo "+JobFlavour           = \"espresso\"" >> $File
echo "" >> $File

WorkDir=$PWD

mkdir -p Log

for GenIndex in `ls GenParticles/ | tr '_.' ' ' | cut -d ' ' -f 2 | sort -n`
do
   for HLTIndex in `ls HLTTree/ | cut -d '.' -f 1 | sort -n`
   do
      echo "Arguments = $WorkDir $GenIndex $HLTIndex" >> $File
      echo "Output    = Log/Run_${GenIndex}_${HLTIndex}.out" >> $File
      echo "Error     = Log/Run_${GenIndex}_${HLTIndex}.err" >> $File
      echo "Log       = Log/Run_${GenIndex}_${HLTIndex}.log" >> $File
      # echo "Queue" >> $File
      echo "" >> $File
   done
done



