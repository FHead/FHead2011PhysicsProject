#!/bin/sh

WORKDIR=~/work/PhysicsWorkspace/HiggsProperties/LightBosonStudies/16322_VectorialFitting

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
eval `scramv1 runtime -sh`
cd -

cp $WORKDIR/RunFit .
cp $WORKDIR/Normalization.dh .

Model=A1UU
Cut=P
ID=1

alias eosbox='/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select root://eosuser.cern.ch'

# eosbox ls /eos/user/c/chenyi/MGSample/

EOSHome=/eos/user/c/chenyi/
Trees16143=$EOSHome/MGSample/16143_FromRoberto_LightBosonBackground/AttachedSpin0XVV//
Trees16153=$EOSHome/MGSample/16153_FromRoberto_LightBosonBackground/AttachedSpin0XVV//
Trees16154=$EOSHome/MGSample/16154_FromRoberto_LightBosonSignalBetterNormalization/AttachedSpin0XVV//
Trees16246=$EOSHome/MGSample/16246_FromRoberto_LightBosonSignal/AttachedSpin0XVV//

echo Start copying files from eosbox space

EOSSEM=$Trees16246/Phto2e2mu_${Model}_18p4GeV_NoPDF_GenCuts_${ID}.root
EOSSEE=$Trees16246/Phto4e_${Model}_18p4GeV_NoPDF_GenCuts_${ID}.root
EOSBEM=$Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root
EOSBEE=$Trees16153/ddbar_noPDF_to_4e_18p4GeV_GenCuts_${ID}.root

for i in `seq 1 100`
do
   if [ ! -s SEM.root ]; then
      eosbox cp $EOSSEM SEM.root
   fi
   if [ ! -s SEE.root ]; then
      eosbox cp $EOSSEE SEE.root
   fi
   if [ ! -s BEM.root ]; then
      eosbox cp $EOSBEM BEM.root
   fi
   if [ ! -s BEE.root ]; then
      eosbox cp $EOSBEE BEE.root
   fi
done

echo
echo Current directory looks like
echo
ls -lh
echo
echo

echo "Model = $Model"
echo "Cut = $Cut"
echo "ID = $ID"

echo Start running 

Tag=${Model}_${Cut}_${ID}

./RunFit SEM.root SEE.root BEM.root BEE.root $Cut $Tag

# cp AllLikelihood_${Model}_${Cut}_${ID}.tar.gz $WORKDIR/Result/

BaseDirAfterWorkspace=`echo $WORKDIR | tr '/' '\n' | grep -A 999 PhysicsWorkspace | tail -n+2 | tr '\n' '/'`
cmsStage -f FitResult_${Tag}.root /store/cmst3/user/chenyi/BatchOutput/$BaseDirAfterWorkspace/Result/FitResult_${Tag}.root




