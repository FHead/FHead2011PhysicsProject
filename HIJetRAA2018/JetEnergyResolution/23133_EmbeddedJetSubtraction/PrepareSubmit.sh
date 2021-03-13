#!/bin/bash

Tag=$1
JetR=$2
RhoPhiEta=$3

SubmitFile=Submit_${Tag}.condor
Script=$PWD/RunJob.sh

mkdir -p $PWD/Output/$Tag/

echo "Universe              = vanilla" > $SubmitFile
echo "Executable            = $Script" >> $SubmitFile
echo "should_transfer_files = NO" >> $SubmitFile
echo "+JobFlavour           = \"workday\"" >> $SubmitFile
echo >> $SubmitFile

Count=0

for Input in Forest/*/HiForest*root
do
   Output=$PWD/Output/$Tag/Jets_`basename $Input`

   echo "Arguments = $PWD/$Input $Output $JetR $RhoPhiEta $PWD/Execute" >> $SubmitFile
   echo "Output    = Log/${Tag}_out.\$(Process)" >> $SubmitFile
   echo "Error     = Log/${Tag}_err.\$(Process)" >> $SubmitFile
   echo "Log       = Log/${Tag}_log.\$(Process)" >> $SubmitFile
   echo "Queue" >> $SubmitFile
   echo >> $SubmitFile

   Count=`echo $Count | AddConst 1`
   if [[ $Count -eq 200 ]]; then
      break
   fi
done


