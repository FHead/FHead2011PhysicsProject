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

# L1=Fall17_17Nov2017_V8_MC_L1FastJet_AK4PFchs.txt
L2L3=Fall17_17Nov2017_V8_MC_L2Relative_AK4PFchs.txt

# L1=bias2SelectionPow_20180523_25nsV1_MC_L1FastJet_AK4PFchs.txt
L1=bias2SelectionPow_20180523_25nsV1_MC_L1FastJet_AK4PFchs_bigrho.txt

$WorkDir/Execute -input Input.root -output Output.root -tree ak4pfchs/t -l1 $L1 -l2l3 $L2L3

cp Output.root __OUTPUT__/Output___ID__.root

