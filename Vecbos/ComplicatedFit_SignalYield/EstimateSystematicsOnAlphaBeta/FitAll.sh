NJet=4

root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", $NJet, \"PF\", 0.423)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", $NJet, \"PF\", 0.423)"
root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", $NJet, \"Calo\", 0.485)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", $NJet, \"Calo\", 0.485)"
root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", $NJet, \"UncorrectedCalo\", 0.426)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", $NJet, \"UncorrectedCalo\", 0.426)"
root -l -b -q "SimultaneousFit_FixRelation.C+(\"Samples/DataAll.root\", $NJet, \"Track\", 0.434)"
root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", $NJet, \"Track\", 0.434)"

