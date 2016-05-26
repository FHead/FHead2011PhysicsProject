#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_7_1_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

echo $HOSTNAME
echo "Current PWD = `pwd`"

BaseDir=/home/yichen/PhysicsWorkspace/HiggsProperties/Fitting/15273_GenFullFitting/
WorkDir=`pwd`

echo "Work directory = $WorkDir"

touch $WorkDir/DummyFile

SEMFile=$1; shift
SEMSize=$1; shift
SEEFile=$1; shift
SEESize=$1; shift
BEMFile1=$1; shift
BEMSize1=$1; shift
BEEFile1=$1; shift
BEESize1=$1; shift
BEMFile2=$1; shift
BEMSize2=$1; shift
BEEFile2=$1; shift
BEESize2=$1; shift
Energy=$1; shift
CutLabel=$1; shift
JobLabel=$1; shift
UUbarDDbarRatio2e2mu=$1; shift
UUbarDDbarRatio4e=$1; shift

cp -r $BaseDir/*cpp $WorkDir/
cp -r $BaseDir/*h $WorkDir/
rm Normalization.dh
ln -s $BaseDir/Trees* $WorkDir/
ln -s $BaseDir/Normalization.dh $WorkDir/

# sh compile.sh
cp $BaseDir/PerformFits .

echo
echo $BEMFile1 $BEMSize1
echo
echo

echo time ./PerformFits \\
echo    $SEMFile $SEMSize $BEMFile1 $BEMSize1 $BEMFile2 $BEMSize2 \\
echo    $SEEFile $SEESize $BEEFile1 $BEESize1 $BEEFile2 $BEESize2 \\
echo    $Energy $CutLabel $UUbarDDbarRatio \\
echo    0 0 0 0.014 0 0 -0.008 0 \\
echo    1 0 173.21 2 79.95 \\
echo
time ./PerformFits \
   $SEMFile $SEMSize $BEMFile1 $BEMSize1 $BEMFile2 $BEMSize2 \
   $SEEFile $SEESize $BEEFile1 $BEESize1 $BEEFile2 $BEESize2 \
   $Energy $CutLabel $UUbarDDbarRatio2e2mu $UUbarDDbarRatio4e \
   0 0 0 0.014 0 0 -0.0081 0 \
   1 0 173.21 2 79.95


mv OutputFile.root $BaseDir/CondorSubmit/Result/FitResult_$JobLabel.root


