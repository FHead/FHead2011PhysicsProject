#!/bin/bash

OutputBase=/eos/user/c/chenyi/Share/21274_FakeJetFourthLook/

rm Submit.condor
touch Submit.condor

echo 'Universe   = vanilla' >> Submit.condor
echo 'Executable = /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetReco2018/DataStudies/21274_FakeJetFourthLook/RunJob.sh' >> Submit.condor
echo 'should_transfer_files = NO' >> Submit.condor
# echo 'requirements = (OpSysAndVer =?= "CentOS7")' >> Submit.condor
echo 'requirements = (OpSysAndVer =?= "SLCern6")' >> Submit.condor
echo >> Submit.condor

Count=0
for i in `ls MB/*/*root | Reformat 2 | grep -v "^[ ]*$" | tr ' ' ','`
do
   echo $i
   Count=`echo $Count | AddConst 1`

   echo "Arguments = $i $OutputBase/Result_${Count}.root" >> Submit.condor
   echo "Output    = Log/RunTrack.out.\$(Process)" >> Submit.condor
   echo "Error     = Log/RunTrack.err.\$(Process)" >> Submit.condor
   echo "Log       = Log/RunTrack.log.\$(Process)" >> Submit.condor
   echo "Queue" >> Submit.condor
   echo >> Submit.condor
done




