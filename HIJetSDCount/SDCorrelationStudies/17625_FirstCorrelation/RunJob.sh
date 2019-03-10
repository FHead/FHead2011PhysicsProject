#!/bin/bash 

WorkDir=__WORKDIR__
SampleName=__SAMPLENAME__
SampleFile=__SAMPLE__
OutputTag=__OUTPUTTAG__
InstallDir=$WorkDir/InstallDir/
SamplesDir=$WorkDir/InstallDir/Samples/$SampleName/smallfiles
ResultDir=$WorkDir/Result/

echo "Work dir = $WorkDir"
echo "Sample name = $SampleName"
echo "Sample file = $SampleFile"
echo "Output tag = $OutputTag"
echo "Install dir = $InstallDir"
echo "Sample dir = $SampleDir"
echo "Result dir = $ResultDir"

source $InstallDir/setup.sh

$InstallDir/runFromFile -hard $SamplesDir/$SampleFile -nev 10000

mv JetToyHIResultFromFile.root $ResultDir/Result___OUTPUTTAG__.root




