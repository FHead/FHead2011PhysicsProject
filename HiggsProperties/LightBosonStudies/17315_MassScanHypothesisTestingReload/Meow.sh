#!/bin/sh

WORKDIR=~/work/PhysicsWorkspace/HiggsProperties/LightBosonStudies/16225_BetterHypothesisTesting

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
eval `scramv1 runtime -sh`
cd -

ln -s $WORKDIR/RunLikelihood .
ln -s $WORKDIR/Normalization.dh .
ln -s $WORKDIR/Trees* .

Model=__MODEL__
Cut=__CUT__
ID=__ID__

Model=A1UU
Cut=P
ID=6

echo "Model = $Model"
echo "Cut = $Cut"
echo "ID = $ID"

./RunLikelihood \
   Trees16154/ggtoPhto2e2mu_${Model}_18p4GeV_noPDF_GenCuts_${ID}.root \
   Trees16154/ggtoPhto4e_${Model}_18p4GeV_noPDF_GenCuts_${ID}.root \
   Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root \
   Trees16153/ddbar_noPDF_to_4e_18p4GeV_GenCuts_${ID}.root \
   $Cut ${Model}_${Cut}_${ID}

tar zcvf AllLikelihood_${Model}_${Cut}_${ID}.tar.gz Likelihood*_${Model}_${Cut}_${ID}_Scenario*

mkdir -p $WORKDIR/Result
mkdir -p $WORKDIR/PDFResult

# cp AllLikelihood_${Model}_${Cut}_${ID}.tar.gz $WORKDIR/Result/

BaseDirAfterWorkspace=`echo $WORKDIR | tr '/' '\n' | grep -A 999 PhysicsWorkspace | tail -n+2 | tr '\n' '/'`
cmsStage AllLikelihood_${Model}_${Cut}_${ID}.tar.gz /store/cmst3/user/chenyi/BatchOutput/$BaseDirAfterWorkspace/Result/AllLikelihood_${Model}_${Cut}_${ID}.tar.gz

mv ResultHypothesisTesting_${Model}_${Cut}_${ID}.pdf $WORKDIR/PDFResult/




