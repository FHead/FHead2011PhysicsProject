CompileRootMacro MakeGraphs.cpp RunGraph

# ./RunGraph 0 Y 80 SD0_MC_PTHat80
# ./RunGraph 0 Y 100 SD0_MC_PTHat100
# ./RunGraph 0 N N SD0_Data
# ./RunGraph 0 N Y SD0_DataPrescale
# ./RunGraph 7 Y 80 SD7_MC_PTHat80
# ./RunGraph 7 Y 100 SD7_MC_PTHat100
# ./RunGraph 7 N N SD7_Data
# ./RunGraph 7 N Y SD7_DataPrescale

CompileRootMacro PickGraphs.cpp RunPickGraph

# ./RunPickGraph 0
# ./RunPickGraph 7

CompileRootMacro MakeSummaryPlots.cpp RunSummary

./RunSummary

mkdir -p PDFPlots

mv Plots/*pdf PDFPlots/
