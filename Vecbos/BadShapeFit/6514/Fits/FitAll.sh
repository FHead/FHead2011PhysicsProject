for i in `seq 400 999`
do
   # root -l -b -q "FitZPeak.C+(\"Normal.root\", $i, $i, 1, 1, 1, 1)"

   for j in 900 950 975 990 1010 1025 1050 1100
   do
      Percentage=`echo $j | DivideConst 1000`
      root -l -b -q "FitZPeak.C+(\"AlphaL$j.root\", $i, $i, $Percentage, 1, 1, 1)"
      root -l -b -q "FitZPeak.C+(\"AlphaR$j.root\", $i, $i, 1, $Percentage, 1, 1)"
      root -l -b -q "FitZPeak.C+(\"SigmaL$j.root\", $i, $i, 1, 1, $Percentage, 1)"
      root -l -b -q "FitZPeak.C+(\"SigmaR$j.root\", $i, $i, 1, 1, 1, $Percentage)"
   done
done
