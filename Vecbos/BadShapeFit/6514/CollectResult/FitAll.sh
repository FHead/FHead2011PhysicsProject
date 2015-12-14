root -l -b -q "DrawNormalYield.C+(\"Results/Normal.root\", 0, 999, \"Normal\")"

for i in AlphaL AlphaR SigmaL SigmaR
do
   for j in 900 950 975 990 1010 1025 1050 1100
   do
      root -l -b -q "DrawNormalYield.C+(\"Results/$i$j.root\", 0, 999, \"$i$j\")"
   done

   root -l -b -q "MakeSummaryPlots.C+(\"$i\", \"${i}Summary\")"
done


