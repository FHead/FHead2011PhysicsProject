
for i in 28
do
   root -l -b -q "MinimumScan.C+(\"Samples/DataAllTrimmedStage2.root\", 4, \"PF\", $i, \"Samples/DataAll.dh\")"
   mv ResultPlots* Result
done

