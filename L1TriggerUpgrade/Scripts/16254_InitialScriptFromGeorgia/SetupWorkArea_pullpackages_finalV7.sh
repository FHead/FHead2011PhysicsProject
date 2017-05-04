# cmsrel CMSSW_6_2_0_SLHC12
# cd CMSSW_6_2_0_SLHC12/src
# cmsenv

git cms-addpkg RecoHI/HiJetAlgos    # for the HeavyIons HLT algorithm

git clone https://github.com/uwcms/UCT2015.git L1Trigger/UCT2015
git cms-addpkg L1Trigger/RegionalCaloTrigger
git cms-addpkg DataFormats/L1CaloTrigger
git cms-addpkg L1TriggerConfig/L1ScalesProducers
patch -N -p0 < L1Trigger/UCT2015/eic9bit.patch


echo SLHCUpgradeSimulations/L1CaloTrigger/ >> .git/info/sparse-checkout
echo SLHCUpgradeSimulations/L1TrackTrigger/  >> .git/info/sparse-checkout
echo SimDataFormats/SLHC/  >> .git/info/sparse-checkout
echo DataFormats/L1TrackTrigger/ >> .git/info/sparse-checkout

git remote add ep git@github.com:EmanuelPerez/cmssw.git
git fetch ep
git checkout TTI_62X_TrackTriggerObjects_V1 -- RecoHI/HiJetAlgos

# --- we need our own SLHCUpgradeSimulations/L1CaloTrigger for :
# ---      1. the new L1Jets from Nick et al
# ---      2. the old definition of the H/E cut in the new stage-2 L1EG algorithm
git checkout TTI_62X_TrackTriggerObjects_V7e -- SLHCUpgradeSimulations/L1CaloTrigger

git checkout TTI_62X_TrackTriggerObjects_V7e -- SLHCUpgradeSimulations/L1TrackTrigger
git checkout TTI_62X_TrackTriggerObjects_V7e -- DataFormats/L1TrackTrigger
git checkout TTI_62X_TrackTriggerObjects_V7e -- SimDataFormats/SLHC

# -- needed for the muons
echo /DataFormats/L1DTPlusTrackTrigger/  >> .git/info/sparse-checkout
echo /L1Trigger/DTPlusTrackTrigger/  >> .git/info/sparse-checkout
echo /L1Trigger/DTTrigger/  >> .git/info/sparse-checkout
echo /L1Trigger/L1ExtraFromDigis/    >> .git/info/sparse-checkout
echo /Geometry/TrackerGeometryBuilder/ >> .git/info/sparse-checkout
echo /L1Trigger/TrackFindingAM/   >> .git/info/sparse-checkout
echo /L1Trigger/TrackFindingTracklet/   >> .git/info/sparse-checkout
echo /DataFormats/L1Trigger/   >> .git/info/sparse-checkout

git checkout  TTI_62X_TrackTriggerObjects_V3c --  DataFormats/L1DTPlusTrackTrigger
git checkout  TTI_62X_TrackTriggerObjects_V3c -- L1Trigger/DTPlusTrackTrigger
git checkout  TTI_62X_TrackTriggerObjects_V3c -- L1Trigger/DTTrigger
git checkout  TTI_62X_TrackTriggerObjects_V3c --  L1Trigger/L1ExtraFromDigis
git checkout  TTI_62X_TrackTriggerObjects_V3c --  Geometry/TrackerGeometryBuilder
git checkout  TTI_62X_TrackTriggerObjects_V3c -- L1Trigger/TrackFindingAM
git checkout  TTI_62X_TrackTriggerObjects_V3c --  L1Trigger/TrackFindingTracklet
git checkout  TTI_62X_TrackTriggerObjects_V4 --  DataFormats/L1Trigger


# --- the following is not necessary if you've started from SLHC12_patch1 instead of SLHC12 :
echo SimTracker/TrackTriggerAssociation/  >> .git/info/sparse-checkout
echo L1Trigger/TrackTrigger/  >> .git/info/sparse-checkout
git checkout TTI_62X_TrackTriggerObjects_V3 -- L1Trigger/TrackTrigger         
git checkout TTI_62X_TrackTriggerObjects_V3 -- SimTracker/TrackTriggerAssociation     
# ---
git clone -b l1ntuple-62X git@github.com:cms-l1trigger-menustudies/L1TriggerUpgrade.git UserCode/L1TriggerUpgrade
#git clone git@github.com:cms-l1trigger-menustudies/L1TriggerUpgrade.git UserCode/L1TriggerUpgrade
git clone git@github.com:cms-l1trigger-menustudies/L1TriggerDPG.git UserCode/L1TriggerDPG
git clone git@github.com:cms-l1trigger-menustudies/MenuGeneration.git L1Trigger/MenuGeneration

scramv1 b -j 8
