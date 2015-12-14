#!/bin/tcsh


set inputfile=$1
set process=$2
set energy=$3
set neventsPerJob=$4
set jobnumber=$5
set outputname=$6
set outputdir=$7



cd    /afs/cern.ch/work/s/sixie/public/releases/syncForRun1LegacyPaper/CMSSW_7_0_0/src
eval `scramv1 runtime -csh`
cd -

ln -sf /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/BuildMap/13156_CollectNormalization/Normalization.dh ./
ln -sf /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/BuildMap/13156_CollectNormalization/CombinedNormalization.dh ./

cp /afs/cern.ch/work/c/chenyi/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan_Si/RunLikelihoodBatch  ./


mkdir -p $outputdir/

./RunLikelihoodBatch ${inputfile} ${neventsPerJob} ${jobnumber} ${energy} ${process} 0 0 0 0 0 0 0 0 -1 
mv LikelihoodFile.root $outputdir/${outputname}_${energy}TeV_channel0_Job${jobnumber}.root
./RunLikelihoodBatch ${inputfile} ${neventsPerJob} ${jobnumber} ${energy} ${process} 1 0 0 0 0 0 0 0 -1 
mv LikelihoodFile.root $outputdir/${outputname}_${energy}TeV_channel1_Job${jobnumber}.root
./RunLikelihoodBatch ${inputfile} ${neventsPerJob} ${jobnumber} ${energy} ${process} 2 0 0 0 0 0 0 0 -1 
mv LikelihoodFile.root $outputdir/${outputname}_${energy}TeV_channel2_Job${jobnumber}.root
./RunLikelihoodBatch ${inputfile} ${neventsPerJob} ${jobnumber} ${energy} ${process} 3 0 0 0 0 0 0 0 -1 
mv LikelihoodFile.root $outputdir/${outputname}_${energy}TeV_channel3_Job${jobnumber}.root



