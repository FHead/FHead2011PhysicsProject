root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", 4, \"PF\", 0.424)"
root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", 4, \"Calo\", 0.485)"

exit

for i in "" LowThreshold HighThreshold LowEtaThreshold HighEtaThreshold
do
   root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", 4, \"PF\", 0.424, \"$i\")"
   root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", 4, \"PF\", 0.424, \"$i\")"
   root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", 4, \"Calo\", 0.485, \"$i\")"
   root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", 4, \"Calo\", 0.485, \"$i\")"
   # root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", 4, \"UncorrectedCalo\", 0.426, \"$i\")"
   # root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", 4, \"UncorrectedCalo\", 0.426, \"$i\")"
   # root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", 4, \"Track\", 0.434, \"$i\")"
   # root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", 4, \"Track\", 0.434, \"$i\")"
done

