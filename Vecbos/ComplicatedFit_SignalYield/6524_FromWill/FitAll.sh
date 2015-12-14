#!/bin/sh

# root -l -b -q "SimultaneousFit.C+(\"Samples/data-w15mt_JECM.root\", 4, \"pf\", 15, \"Samples/datau_JECM.dh\", false)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data-w30mt_JECM.root\", 4, \"pf\", 30, \"Samples/datau_JECM.dh\", false)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data-w15mt_JECM.root\", 4, \"pf\", 15, \"Samples/dataw_JECM.dh\", true)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data-w30mt_JECM.root\", 4, \"pf\", 30, \"Samples/dataw_JECM.dh\", true)"

# mv ResultPlot* Minus/
# mv ComplicatedFit* Minus/
# mv FitYields* Minus/

# root -l -b -q "SimultaneousFit.C+(\"Samples/data-w15mt_JECP.root\", 4, \"pf\", 15, \"Samples/datau_JECP.dh\", false)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data-w30mt_JECP.root\", 4, \"pf\", 30, \"Samples/datau_JECP.dh\", false)"
root -l -b -q "SimultaneousFit.C+(\"Samples/data-w15mt_JECP.root\", 4, \"pf\", 15, \"Samples/dataw_JECP.dh\", true)"
# root -l -b -q "SimultaneousFit.C+(\"Samples/data-w30mt_JECP.root\", 4, \"pf\", 30, \"Samples/dataw_JECP.dh\", true)"

mv ResultPlot* Plus/
mv ComplicatedFit* Plus/
mv FitYields* Plus/





