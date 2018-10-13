#!/bin/sh --login

#BSUB -q 8nh

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HI2018HLT/JetTriggers/17573_RatesXeXe

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_10_1_8/src
eval `scramv1 runtime -sh`
cd - > /dev/null

export X509_USER_PROXY=$PhysicsWorkspace/HI2018HLT/CommonCode/proxy/x509up_proxy
echo $X509_USER_PROXY

echo "ID = __ID__"

cp $WorkDir/Result/RunJob___ID__.py.bz2 .
cp $WorkDir/setup_dev_CMSSW_10_1_0_GRun_cff.py .

bunzip2 RunJob___ID__.py.bz2

ln -s $SampleBase Samples

mkdir -p $WorkDir/Result/

cmsRun RunJob___ID__.py >& Log___ID__
bzip2 Log___ID__
mv Log___ID__.bz2 $WorkDir/Result/
mv openHLT.root $WorkDir/Result/openHLT___ID__.root

