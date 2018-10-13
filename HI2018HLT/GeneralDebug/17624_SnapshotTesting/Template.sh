#!/bin/sh --login

#BSUB -q 1nd

WorkDir=__WORKDIR__

export SCRAM_ARCH=slc6_amd64_gcc630
cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_10_3_X_2018-09-19-1100/src/
eval `scramv1 runtime -sh`
cd - > /dev/null

export X509_USER_PROXY=$PhysicsWorkspace/HI2018HLT/CommonCode/proxy/x509up_proxy
echo $X509_USER_PROXY

Template=$WorkDir/ExportedMenuV18.py

FileList=`echo "__INPUT__" | tr '@' ' ' | sed "s/[ ,]*$//"`

echo $FileList
echo "ID = __ID__"

cat $Template \
   | sed "s#__FILE__#$FileList#g" \
   > RunJob.py
cp RunJob.py RunJobBackup.py
bzip2 RunJobBackup.py
mv RunJobBackup.py.bz2 $WorkDir/Result/RunJob___ID__.py.bz2

mkdir -p $WorkDir/Result/

cmsRun RunJob.py >& Log___ID__
bzip2 Log___ID__
mv Log___ID__.bz2 $WorkDir/Result/
mv openHLT.root $WorkDir/Result/openHLT___ID__.root
tar cvfz JSD.tar.gz run000001*
mv JSD.tar.gz $WorkDir/Result/JSR___ID__.tar.gz


