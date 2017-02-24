CompileRootMacro MakeGraphs.cpp RunGraph

./RunGraph 0 Y 80 SD0_MC_PTHat80
./RunGraph 0 Y 100 SD0_MC_PTHat100
./RunGraph 0 N 0 SD0_Data
./RunGraph 7 Y 80 SD7_MC_PTHat80
./RunGraph 7 Y 100 SD7_MC_PTHat100
./RunGraph 7 N 0 SD7_Data

CompileRootMacro MakeSummaryPlots.cpp RunSummary

./RunSummary

mkdir -p PDFPlots

mv Plots/*pdf PDFPlots/
