#!/bin/sh --login

#BSUB -q 1nh

WorkDir=__WORKDIR__

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_9_4_3/src
eval `scramv1 runtime -sh`
cd - > /dev/null

cp $WorkDir/*txt .

echo Input files are: __FILE__

hadd -k -f Input.root __FILE__

$WorkDir/Execute -input Input.root -output Output.root -l1 __L1__ -l2l3 __L2L3__ -tree __TREE__

cp Output.root __OUTPUT__/Output___ID__.root

