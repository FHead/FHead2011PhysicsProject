#!/bin/bash

BaseDir=~/work/PhysicsWorkspace/HIJetSDCount/FourierTransform/21361_CenteringJets

export SCRAM_ARCH=slc6_amd64_gcc491; cd ~/work/CMSSW/CMSSW_10_3_3_patch1/src; eval `scramv1 runtime -sh`; cd - > /dev/null; export CMSSW_SEARCH_PATH=$CMSSW_SEARCH_PATH:~/work/CMSSW/CMSSW_10_3_3_patch1/work/EssentialFiles

File=$1
Start=`expr $File '*' 300`
End=`expr $Start '+' 299`


$BaseDir/RunExport \
   $BaseDir/Hydjet/60k_CentralFivePercent/RunOutput_${File}.root \
   $BaseDir/Pythia/Output.root Output.root ${Start} ${End} ${File}

mv Output.root $BaseDir/Output/JetTree_${File}.root




