#!/bin/bash

EOSBase=/eos/cms/store/group/phys_heavyions/chenyi/Samples/

function CopyDirectory()
{
   echo Start processing files from $1
   
   xrdfs xrootd.cmsaf.mit.edu ls "$1" > TEMP

   mkdir -p $EOSBase/$1/

   for i in `cat TEMP`
   do
      xrdcp root://xrootd.cmsaf.mit.edu/$i $EOSBase/$1/
   done

   rm TEMP
}

# HP, EE fix, yes MVA
# CopyDirectory "/store/user/katatar/relval/HIHardProbes/CMSSW_10_3_3-103X_dataRun2_Prompt_fixEcalADCToGeV_v1_newMVA_rsb_RelVal_hi2018hardprobes-v1-FOREST/190401_165756/0000/"

# HP, EE fix, no MVA
# CopyDirectory "/store/user/katatar/relval/HIHardProbes/CMSSW_10_3_3-103X_dataRun2_Prompt_fixEcalADCToGeV_v1_default_RelVal_hi2018hardprobes-v1-FOREST/190401_171144/0000/"

# MB, EE fix, no MVA
# CopyDirectory "/store/user/katatar/relval/HIMinimumBias0/CMSSW_10_3_3-103X_dataRun2_Prompt_fixEcalADCToGeV_v1_default_rsb_RelVal_hi2018-v1-FOREST/190401_170045/0000/" 

# MB, no EE fix, no MVA
# CopyDirectory "/store/user/katatar/relval/HIMinimumBias0/CMSSW_10_3_3-103X_dataRun2_Prompt_v2_default_rsb_RelVal_hi2018-v1-FOREST/190401_165949/0000/"

# MB, no EE fix, with MVA
CopyDirectory "/store/user/katatar/relval/HIMinimumBias0/CMSSW_10_3_3-103X_dataRun2_Prompt_v2_newMVA_rsb_RelVal_hi2018-v1-FOREST/190402_142527/0000/"

touch DoneCopying

