
for i in 40
do
   root -l -b -q "LimitScan.C+(\"Samples/DataAllTrimmedStage2.root\", 4, \"PF\", $i, \"Samples/DataAll.dh\")"
   mv ResultPlot* Result/
done

