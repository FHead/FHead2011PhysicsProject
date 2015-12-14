#!/bin/sh

# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, \"Samples/data_w15_weighted_D6T.dh\", true, \"Samples/D6TPF15SmearingMatrix\")"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15.root\", 4, \"pf\", 15, \"Samples/data_w15_unweighted_D6T.dh\", false, \"Samples/D6TPF15SmearingMatrix\")"

# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, \"Samples/data_w30_weighted_D6T.dh\", true, \"Samples/D6TPF30SmearingMatrix\")"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30.root\", 4, \"pf\", 30, \"Samples/data_w30_unweighted_D6T.dh\", false, \"Samples/D6TPF30SmearingMatrix\")"

# mv ComplicatedFit* Normal/
# mv FitYields* Normal/
# mv ResultPlots* Normal/
# mv UnfoldedResult* Normal/


# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15P.root\", 4, \"pf\", 15, \"Samples/data_w15P_weighted_D6T.dh\", true, \"Samples/D6TPF15SmearingMatrix\")"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15P.root\", 4, \"pf\", 15, \"Samples/data_w15P_unweighted_D6T.dh\", false, \"Samples/D6TPF15SmearingMatrix\")"

root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30P.root\", 4, \"pf\", 30, \"Samples/data_w30P_weighted_D6T.dh\", true, \"Samples/D6TPF30SmearingMatrix\")"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30P.root\", 4, \"pf\", 30, \"Samples/data_w30P_unweighted_D6T.dh\", false, \"Samples/D6TPF30SmearingMatrix\")"

mv ComplicatedFit* Plus/
mv FitYields* Plus/
mv ResultPlots* Plus/
mv UnfoldedResult* Plus/


# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15M.root\", 4, \"pf\", 15, \"Samples/data_w15M_weighted_D6T.dh\", true, \"Samples/D6TPF15SmearingMatrix\")"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w15M.root\", 4, \"pf\", 15, \"Samples/data_w15M_unweighted_D6T.dh\", false, \"Samples/D6TPF15SmearingMatrix\")"

# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30M.root\", 4, \"pf\", 30, \"Samples/data_w30M_weighted_D6T.dh\", true, \"Samples/D6TPF30SmearingMatrix\")"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data_w30M.root\", 4, \"pf\", 30, \"Samples/data_w30M_unweighted_D6T.dh\", false, \"Samples/D6TPF30SmearingMatrix\")"

# mv ComplicatedFit* Minus/
# mv FitYields* Minus/
# mv ResultPlots* Minus/
# mv UnfoldedResult* Minus/


