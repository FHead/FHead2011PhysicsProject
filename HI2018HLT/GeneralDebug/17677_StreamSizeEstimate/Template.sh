#!/bin/sh --login

#BSUB -q 2nd

WorkDir=__WORKDIR__
SampleType=__SAMPLETYPE__
ID=__ID__

export SCRAM_ARCH=slc6_amd64_gcc700
cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_10_3_0/src/
eval `scramv1 runtime -sh`
cd - > /dev/null

export X509_USER_PROXY=$PhysicsWorkspace/HI2018HLT/CommonCode/proxy/x509up_proxy
echo $X509_USER_PROXY

Template=$WorkDir/ExportedMenuOnlineV1.0V11.py

FileList=`echo "__INPUT__" | tr '@' ' ' | sed "s/[ ,]*$//"`

echo "List of files = $FileList"
echo "ID = $ID"
echo "Sample = $SampleType"

cat $Template \
   | sed "s#__FILE__#$FileList#g" \
   > RunJob.py
cat RunJob.py | bzip2 > $WorkDir/Result/RunJob_${SampleType}_${ID}.py.bz2

cp $WorkDir/setup_dev_CMSSW_10_3_0_HLT_cff.py .
cp -r $WorkDir/Sample* .

mkdir -p $WorkDir/Result/

cmsRun RunJob.py >& Log_${ID}
bzip2 Log_${ID}
mkdir -p $WorkDir/Result/${ID}/
mv Log_${ID}.bz2 $WorkDir/Result/${ID}/Log_${SampleType}_${ID}.bz2
mv output*root $WorkDir/Result/${ID}/

