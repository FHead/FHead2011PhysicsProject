for i in 0.0_0.5 0.5_0.9 0.9_1.3
do
   AbsEtaMin=`echo $i | tr '_' ' ' | awk '{print $1}'`
   AbsEtaMax=`echo $i | tr '_' ' ' | awk '{print $2}'`

   for j in 0_50 50_100 100_150 150_200 200_250 250_350
   do
      RhoMin=`echo $j | tr '_' ' ' | awk '{print $1}'`
      RhoMax=`echo $j | tr '_' ' ' | awk '{print $2}'`

      LOG=FitPlots/FitResultLog_${AbsEtaMin}_${AbsEtaMax}_${RhoMin}_${RhoMax}

      echo Starting fit with eta = $AbsEtaMin-$AbsEtaMax, rho = $RhoMin-$RhoMax
      ./b.out $AbsEtaMin $AbsEtaMax $RhoMin $RhoMax >& $LOG
      grep FITRESULT $LOG
   done
done
