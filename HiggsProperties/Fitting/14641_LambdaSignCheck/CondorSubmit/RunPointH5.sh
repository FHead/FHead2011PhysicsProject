#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_7_1_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/Fitting/14641_LambdaSignCheck/
WorkDir=`pwd`

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

SEMFile=$1; shift
SEMSize=$1; shift
SEEFile=$1; shift
SEESize=$1; shift
BEMFile=$1; shift
BEMSize=$1; shift
BEEFile=$1; shift
BEESize=$1; shift
CutLabel=$1; shift
JobLabel=$1; shift

cp -r $BaseDir/*cpp $WorkDir/
cp -r $BaseDir/*h $WorkDir/
rm Normalization.dh
ln -s $BaseDir/TreeLinks $WorkDir/
ln -s $BaseDir/Normalization.dh $WorkDir/

sh compile.sh

echo time ./PerformFits \\
echo    $SEMFile $SEMSize $BEMFile $BEMSize \\
echo    $SEEFile $SEESize $BEEFile $BEESize \\
echo    $CutLabel \\
echo    0 0 0 0.014 0 -0.0078 -0.0081 0 \\
echo
time ./PerformFits \
   $SEMFile $SEMSize $BEMFile $BEMSize \
   $SEEFile $SEESize $BEEFile $BEESize \
   $CutLabel \
   0 0 0 -0.00750 0 0 0.005 0 \
   0 0 173.21 -1 79.95

mv OutputFile.root $BaseDir/CondorSubmit/Result/FitResult_$JobLabel.root


