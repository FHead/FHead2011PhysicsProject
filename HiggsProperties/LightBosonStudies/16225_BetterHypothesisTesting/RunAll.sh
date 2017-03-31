export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
eval `scramv1 runtime -sh`

WORKDIR=`pwd`

echo Moving to $WORKDIR
cd $WORKDIR

for ID in `seq 2 10`
do
   for Cut in P F
   do
      for Model in A1UU A2UU A3UU A2UA A2UZ A1UUpA3UU A1UURTpA1UZRI A1UURpA1UR
      do
      ./RunLikelihood \
         Trees16154/ggtoPhto2e2mu_${Model}_18p4GeV_noPDF_GenCuts_${ID}.root \
         Trees16154/ggtoPhto4e_${Model}_18p4GeV_noPDF_GenCuts_${ID}.root \
         Trees16143/ddbar_noPDF_to_2e2mu_18p4GeV_GenCuts_${ID}.root \
         Trees16153/ddbar_noPDF_to_4e_18p4GeV_GenCuts_${ID}.root \
         $Cut ${Model}_${Cut}_${ID}
      done
   done
done
