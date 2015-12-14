#!/bin/sh

PF15Smear="\"Samples/PF15SmearingMatrix\""
PF30Smear="\"Samples/PF30SmearingMatrix\""
NoSmear="\"Samples/UnitMatrix\""

# Dimensions: NoJEC x Unfold/NoUnfold x Unweighted/WeightMinus/Weight/WeightPlus

# Unweighted
# Data="\"Samples/data_w15.root\""
# DHFile="\"Samples/NoJEC_NoUnfold_Unweighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, false, $NoSmear)"
# mv ComplicatedFit* NoJEC_NoUnfold_Unweighted/
# mv FitYields* NoJEC_NoUnfold_Unweighted/
# mv ResultPlots* NoJEC_NoUnfold_Unweighted/
# mv UnfoldedResult* NoJEC_NoUnfold_Unweighted/

# Data="\"Samples/data_w15.root\""
# DHFile="\"Samples/NoJEC_Unfold_Unweighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, false, $PF15Smear)"
# mv ComplicatedFit* NoJEC_Unfold_Unweighted/
# mv FitYields* NoJEC_Unfold_Unweighted/
# mv ResultPlots* NoJEC_Unfold_Unweighted/
# mv UnfoldedResult* NoJEC_Unfold_Unweighted/

# Data="\"Samples/data_w30.root\""
# DHFile="\"Samples/NoJEC_NoUnfold_Unweighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, false, $NoSmear)"
# mv ComplicatedFit* NoJEC_NoUnfold_Unweighted/
# mv FitYields* NoJEC_NoUnfold_Unweighted/
# mv ResultPlots* NoJEC_NoUnfold_Unweighted/
# mv UnfoldedResult* NoJEC_NoUnfold_Unweighted/

# Data="\"Samples/data_w30.root\""
# DHFile="\"Samples/NoJEC_Unfold_Unweighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, false, $PF30Smear)"
# mv ComplicatedFit* NoJEC_Unfold_Unweighted/
# mv FitYields* NoJEC_Unfold_Unweighted/
# mv ResultPlots* NoJEC_Unfold_Unweighted/
# mv UnfoldedResult* NoJEC_Unfold_Unweighted/


# Normally weighted
# Data="\"Samples/data_w15.root\""
# DHFile="\"Samples/NoJEC_NoUnfold_Weighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, true, $NoSmear)"
# mv ComplicatedFit* NoJEC_NoUnfold_Weighted/
# mv FitYields* NoJEC_NoUnfold_Weighted/
# mv ResultPlots* NoJEC_NoUnfold_Weighted/
# mv UnfoldedResult* NoJEC_NoUnfold_Weighted/

# Data="\"Samples/data_w15.root\""
# DHFile="\"Samples/NoJEC_Unfold_Weighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, true, $PF15Smear)"
# mv ComplicatedFit* NoJEC_Unfold_Weighted/
# mv FitYields* NoJEC_Unfold_Weighted/
# mv ResultPlots* NoJEC_Unfold_Weighted/
# mv UnfoldedResult* NoJEC_Unfold_Weighted/

# Data="\"Samples/data_w30.root\""
# DHFile="\"Samples/NoJEC_NoUnfold_Weighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $NoSmear)"
# mv ComplicatedFit* NoJEC_NoUnfold_Weighted/
# mv FitYields* NoJEC_NoUnfold_Weighted/
# mv ResultPlots* NoJEC_NoUnfold_Weighted/
# mv UnfoldedResult* NoJEC_NoUnfold_Weighted/

# Data="\"Samples/data_w30.root\""
# DHFile="\"Samples/NoJEC_Unfold_Weighted.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear)"
# mv ComplicatedFit* NoJEC_Unfold_Weighted/
# mv FitYields* NoJEC_Unfold_Weighted/
# mv ResultPlots* NoJEC_Unfold_Weighted/
# mv UnfoldedResult* NoJEC_Unfold_Weighted/


# Weight plus
# Data="\"Samples/data_w15P.root\""
# DHFile="\"Samples/NoJEC_NoUnfold_WeightPlus.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, true, $NoSmear)"
# mv ComplicatedFit* NoJEC_NoUnfold_WeightPlus/
# mv FitYields* NoJEC_NoUnfold_WeightPlus/
# mv ResultPlots* NoJEC_NoUnfold_WeightPlus/
# mv UnfoldedResult* NoJEC_NoUnfold_WeightPlus/

# Data="\"Samples/data_w15P.root\""
# DHFile="\"Samples/NoJEC_Unfold_WeightPlus.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, true, $PF15Smear)"
# mv ComplicatedFit* NoJEC_Unfold_WeightPlus/
# mv FitYields* NoJEC_Unfold_WeightPlus/
# mv ResultPlots* NoJEC_Unfold_WeightPlus/
# mv UnfoldedResult* NoJEC_Unfold_WeightPlus/

# Data="\"Samples/data_w30P.root\""
# DHFile="\"Samples/NoJEC_NoUnfold_WeightPlus.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $NoSmear)"
# mv ComplicatedFit* NoJEC_NoUnfold_WeightPlus/
# mv FitYields* NoJEC_NoUnfold_WeightPlus/
# mv ResultPlots* NoJEC_NoUnfold_WeightPlus/
# mv UnfoldedResult* NoJEC_NoUnfold_WeightPlus/

Data="\"Samples/data_w30P.root\""
DHFile="\"Samples/NoJEC_Unfold_WeightPlus.dh\""
root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear)"
mv ComplicatedFit* NoJEC_Unfold_WeightPlus/
mv FitYields* NoJEC_Unfold_WeightPlus/
mv ResultPlots* NoJEC_Unfold_WeightPlus/
mv UnfoldedResult* NoJEC_Unfold_WeightPlus/


# Weight minus
# Data="\"Samples/data_w15M.root\""
# DHFile="\"Samples/NoJEC_NoUnfold_WeightMinus.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, true, $NoSmear)"
# mv ComplicatedFit* NoJEC_NoUnfold_WeightMinus/
# mv FitYields* NoJEC_NoUnfold_WeightMinus/
# mv ResultPlots* NoJEC_NoUnfold_WeightMinus/
# mv UnfoldedResult* NoJEC_NoUnfold_WeightMinus/

# Data="\"Samples/data_w15M.root\""
# DHFile="\"Samples/NoJEC_Unfold_WeightMinus.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 15, $DHFile, true, $PF15Smear)"
# mv ComplicatedFit* NoJEC_Unfold_WeightMinus/
# mv FitYields* NoJEC_Unfold_WeightMinus/
# mv ResultPlots* NoJEC_Unfold_WeightMinus/
# mv UnfoldedResult* NoJEC_Unfold_WeightMinus/

# Data="\"Samples/data_w30M.root\""
# DHFile="\"Samples/NoJEC_NoUnfold_WeightMinus.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $NoSmear)"
# mv ComplicatedFit* NoJEC_NoUnfold_WeightMinus/
# mv FitYields* NoJEC_NoUnfold_WeightMinus/
# mv ResultPlots* NoJEC_NoUnfold_WeightMinus/
# mv UnfoldedResult* NoJEC_NoUnfold_WeightMinus/

# Data="\"Samples/data_w30M.root\""
# DHFile="\"Samples/NoJEC_Unfold_WeightMinus.dh\""
# root -l -b -q "SimultaneousFit.C+($Data, 4, \"pf\", 30, $DHFile, true, $PF30Smear)"
# mv ComplicatedFit* NoJEC_Unfold_WeightMinus/
# mv FitYields* NoJEC_Unfold_WeightMinus/
# mv ResultPlots* NoJEC_Unfold_WeightMinus/
# mv UnfoldedResult* NoJEC_Unfold_WeightMinus/






























