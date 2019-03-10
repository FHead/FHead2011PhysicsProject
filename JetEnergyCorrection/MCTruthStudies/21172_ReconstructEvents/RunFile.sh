#!/bin/bash

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/JetEnergyCorrection/CommonCode/Proxy/x509up_proxy

SetupScript=$1
CMSSWScript=$2
InputFile=$3
OutputLocation=$4
RandomSeed=$5

echo Setup:
echo    SetupScript = $SetupScript
echo    CMSSWScript = $CMSSWScript
echo    InputFile = $InputFile
echo    OutputLocation = $OutputLocation
echo    RandomNumberSeed = $RandomSeed
echo

cp $3 pickevents.root
cp $1 .
cp $2 Execute.sh
bash Execute.sh $RandomSeed

echo Done.
echo Directory Content:
ls -l
echo

mkdir -p $OutputLocation
mv JME* $OutputLocation

echo Output location content:
ls -l $OutputLocation
echo

rm *root
rm *sh
rm *cc
rm *xml
rm *py
