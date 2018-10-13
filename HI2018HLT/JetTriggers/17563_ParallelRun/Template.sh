#!/bin/sh --login

#BSUB -q 8nh

WorkDir=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HI2018HLT/JetTriggers/17563_ParallelRun
SampleBase=/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/ikucher/TTbar_5020GeV_TuneCUETP8M1_DIGI_L1_DIGI2RAW_HLT_PU/TTbar_5020GeV_TuneCUETP8M1_GEN_SIM_PU/crab_TTbar_5020GeV_TuneCUETP8M1_DIGI_L1_DIGI2RAW_HLT_PU/180724_211145/0000///

export SCRAM_ARCH=slc6_amd64_gcc630
cd ~/work/CMSSW/CMSSW_10_1_8/src
eval `scramv1 runtime -sh`
cd - > /dev/null

export X509_USER_PROXY=$PhysicsWorkspace/HI2018HLT/CommonCode/proxy/x509up_proxy
echo $X509_USER_PROXY

Template=$WorkDir/ExportedMenuV46.py

FileList=`echo "__INPUT__" | tr '@' ' ' | sed "s/[ ,]*$//"`

echo $FileList
echo "ID = __ID__"

cat $Template \
   | sed "s#__FILE__#$FileList#g" \
   > RunJob.py
cp RunJob.py $WorkDir/Result/RunJob___ID__.py

cp $WorkDir/setup_dev_CMSSW_10_1_0_GRun_cff.py .

ln -s $SampleBase Samples

mkdir -p $WorkDir/Result/

cmsRun RunJob.py >& Log___ID__
bzip2 Log___ID__
mv Log___ID__.bz2 $WorkDir/Result/
mv openHLT.root $WorkDir/Result/openHLT___ID__.root

