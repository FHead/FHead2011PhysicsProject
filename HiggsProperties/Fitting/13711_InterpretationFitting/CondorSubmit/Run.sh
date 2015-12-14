#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_6_0_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/Fitting/13711_InterpretationFitting/
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

ln -s $BaseDir/*cpp $WorkDir/
ln -s $BaseDir/*h $WorkDir/
ln -s $BaseDir/Trees $WorkDir/
ln -s $BaseDir/TreeLinks $WorkDir/
ln -s $BaseDir/Trees13466 $WorkDir/
ln -s $BaseDir/../../Normalization.dh $WorkDir/

sh compile.sh

echo time ./PerformFits \\
echo    $SEMFile $SEMSize $BEMFile $BEMSize \\
echo    $SEEFile $SEESize $BEEFile $BEESize \\
echo    $CutLabel \\
echo    0.005 0 0.0045 0 1 0 173.948
time ./PerformFits \
   $SEMFile $SEMSize $BEMFile $BEMSize \
   $SEEFile $SEESize $BEEFile $BEESize \
   $CutLabel \
   0.005 0 0.0045 0 1.0 0 173.21 2 79.9492

mv OutputFile.root $BaseDir/CondorSubmit/Result/FitResult_$JobLabel.root


