CompileRootMacro MakeGraphs.cpp RunGraph

./RunGraph 0 Y 100 SD0_MC
# ./RunGraph 0 N NONE SD0_Data
# ./RunGraph 0 N 100 SD0_DataPrescale_100
# ./RunGraph 0 N 80 SD0_DataPrescale_80
# ./RunGraph 0 N 60 SD0_DataPrescale_60
./RunGraph 7 Y 100 SD7_MC
# ./RunGraph 7 N NONE SD7_Data
# ./RunGraph 7 N 100 SD7_DataPrescale_100
# ./RunGraph 7 N 80 SD7_DataPrescale_80
# ./RunGraph 7 N 60 SD7_DataPrescale_60

CompileRootMacro PickGraphs.cpp RunPickGraph

./RunPickGraph 0
./RunPickGraph 7

CompileRootMacro MakeSummaryPlots.cpp RunSummary

./RunSummary

mkdir -p PDFPlots

mv Plots/*pdf PDFPlots/
