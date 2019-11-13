for i in _RunABC_ _RunD_ _
do
   for j in AK4PF AK4PFchs AK4PFPuppi AK8PF AK8PFchs AK8PFPuppi
   do
      MCJER=JRDatabase/Autumn18${i}V7b_MC/Autumn18${i}V7b_MC_PtResolution_${j}.txt
      JERSF=JRDatabase/Autumn18${i}V7b_MC/Autumn18${i}V7b_MC_SF_${j}.txt
      DataJER=JRDatabase/Autumn18${i}V7b_DATA/Autumn18${i}V7b_DATA_PtResolution_${j}.txt
      Output=Result${i}${j}.root

      ./Execute --MCJER $MCJER --JERSF $JERSF --DataJER $DataJER --Output $Output --N 50000
   done
done
