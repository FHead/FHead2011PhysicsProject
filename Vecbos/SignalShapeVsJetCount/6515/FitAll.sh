for i in PF Track UncorrectedCalo Calo
do
   root -l -b -q "FitZPeak.C+(\"Samples/ZJetsTrimmedStage2.root\", \"$i\")"
   mv Output.root $i.root
done


