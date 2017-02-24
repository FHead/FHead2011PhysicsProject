for i in 0.0_0.5 0.5_0.9 0.9_1.3
do
   AbsEtaMin=`echo $i | tr '_' ' ' | awk '{print $1}'`
   AbsEtaMax=`echo $i | tr '_' ' ' | awk '{print $2}'`

   LOG=FitPlots/FitResultLogNoRho_${AbsEtaMin}_${AbsEtaMax}

   echo Starting fit with eta = $AbsEtaMin-$AbsEtaMax
   ./c.out $AbsEtaMin $AbsEtaMax >& $LOG
   grep FITRESULT $LOG
done
