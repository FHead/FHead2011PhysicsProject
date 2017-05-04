#!/bin/sh --login

#BSUB -q 2nd

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_6_2_0_SLHC12/src
eval `scramv1 runtime -sh`
cd - > /dev/null

WorkDirectory=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/L1TriggerUpgrade/SampleProcessing/16273_PhotonSamples/

PU=__PU__
File=__File__

cat $WorkDirectory/template.py | sed "s/__TemplatePU__/$PU/g" | sed "s/__TemplateFile__/$File/g" > RunCMSSW.py

cmsRun RunCMSSW.py

cmsStage L1Tree.root /store/cmst3/user/chenyi/BatchOutput/L1TriggerUpgrade/SampleProcessing/16273_PhotonSamples/Result/PU$PU/$File


