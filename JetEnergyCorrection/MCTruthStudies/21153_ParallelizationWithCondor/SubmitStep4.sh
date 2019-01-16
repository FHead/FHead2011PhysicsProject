#!/bin/sh

source Setup_FileLocation.sh

Input=$WithPUFiles
Output=$Step4Output
mkdir -p $Step4Output

mkdir -p Log
SubmissionFile=Step4.condor

echo "Universe   = vanilla" > $SubmissionFile
echo "Executable = `pwd`/Step4Closure.sh" >> $SubmissionFile
echo >> $SubmissionFile

Count=0
for File in `ls $Input | Reformat 20 | tr ' ' ':'`
do
   echo $File

   echo "Arguments = `pwd` $File $Output $Count" >> $SubmissionFile
   echo 'Output    = Log/Step3.out.$(Process)' >> $SubmissionFile
   echo 'Error     = Log/Step3.err.$(Process)' >> $SubmissionFile
   echo 'Log       = Log/Step3.log.$(Process)' >> $SubmissionFile
   echo 'Queue' >> $SubmissionFile
   echo >> $SubmissionFile

   Count=`echo $Count | AddConst 1`
done

condor_submit $SubmissionFile
