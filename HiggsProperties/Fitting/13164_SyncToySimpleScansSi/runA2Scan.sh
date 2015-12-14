#!/bin/tcsh


set a2a1=$1
set FloatParameters=$2
set FloatPhases=$3
set FloatFs=$4
set constrainA3Positive=$5
set lumiFactor=$6
set outputname=$7
set outputdir=$8



cd    /afs/cern.ch/work/s/sixie/public/releases/syncForRun1LegacyPaper/CMSSW_7_0_0/src
eval `scramv1 runtime -csh`
cd -

ln -sf /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/BuildMap/13156_CollectNormalization/Normalization.dh ./
ln -sf /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/BuildMap/13156_CollectNormalization/CombinedNormalization.dh ./


/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/RunLikelihoodScan /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_SMSignal.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_SMSignal.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root ${a2a1} 0 0 0 0 0 0 0 ${FloatParameters} ${FloatPhases} ${FloatFs} ${lumiFactor} N ${constrainA3Positive}


  mv LikelihoodFile.root $outputname
  mkdir -p $outputdir/
  mv $outputname $outputdir/

