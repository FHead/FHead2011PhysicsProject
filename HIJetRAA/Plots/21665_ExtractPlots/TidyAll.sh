mkdir -p TidyRoot

# for i in `ls Root | grep ^spectra_`
# do
#    echo $i
#    ./Tidy --Input Root/$i --Output TidyRoot/$i --IsSpectra true
# done
# 
# hadd -f Spectra_Smooth.root TidyRoot/spectra_*_Smooth_*root
# hadd -f Spectra_NotSmooth.root TidyRoot/spectra_*_NotSmooth_*root

# for i in `ls Root | grep ^raa_`
# do
#    echo $i
#    ./Tidy --Input Root/$i --Output TidyRoot/$i --IsRAA true
# done
# 
# hadd -f RAA_Smooth.root TidyRoot/raa_*_Smooth_*root
# hadd -f RAA_NotSmooth.root TidyRoot/raa_*_NotSmooth_*root

# for i in `ls Root | grep ^rraa_`
# do
#    echo $i
#    ./Tidy --Input Root/$i --Output TidyRoot/$i --IsRRAA true
# done
# 
# hadd -f RRAA_NotSmooth_NotRedStat.root TidyRoot/rraa_*_NotSmooth_NotRedStat_*root
# hadd -f RRAA_NotSmooth_RedStat.root TidyRoot/rraa_*_NotSmooth_RedStat_*root
# hadd -f RRAA_Smooth_NotRedStat.root TidyRoot/rraa_*_Smooth_NotRedStat_*root
# hadd -f RRAA_Smooth_RedStat.root TidyRoot/rraa_*_Smooth_RedStat_*root

# for i in `ls Root | grep ^syst_spectra_`
# do
#    echo $i
#    ./Tidy --Input Root/$i --Output TidyRoot/$i --IsSysSpectra true
# done
# 
# hadd -f SysSpectra_Smooth.root TidyRoot/syst_spectra_*_Smooth_*.root
# hadd -f SysSpectra_NotSmooth.root TidyRoot/syst_spectra_*_NotSmooth_*.root

# for i in `ls Root | grep ^syst_raa_`
# do
#    echo $i
#    ./Tidy --Input Root/$i --Output TidyRoot/$i --IsSysRAA true
# done
# 
# hadd -f SysRAA_Smooth.root TidyRoot/syst_raa_*_Smooth_*.root
# hadd -f SysRAA_NotSmooth.root TidyRoot/syst_raa_*_NotSmooth_*.root

for i in `ls Root | grep ^syst_rraa_`
do
   echo $i
   ./Tidy --Input Root/$i --Output TidyRoot/$i --IsSysRRAA true
done

hadd -f SysRRAA_Smooth.root TidyRoot/syst_rraa_*_Smooth_*.root
hadd -f SysRRAA_NotSmooth.root TidyRoot/syst_rraa_*_NotSmooth_*.root

