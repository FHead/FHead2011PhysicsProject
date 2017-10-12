CompileRootMacro ReadTree.cpp ReadTree.o -c | grep -v warning
CompileRootMacro JetEnergyScale.cpp JetEnergyScale.o -c | grep -v warning
CompileRootMacro MakeGraphs.cpp RunGraph ReadTree.o JetEnergyScale.o

./RunGraph 0 N NONE SD0_Data; mv JESCheck.pdf JESData.pdf
# ./RunGraph 0 N 100 SD0_DataPrescale_100; mv JESCheck.pdf JESDataPrescale100.pdf
./RunGraph 0 N 80 SD0_DataPrescale_80; mv JESCheck.pdf JESDataPrescale80.pdf
./RunGraph 0 N 60 SD0_DataPrescale_60; mv JESCheck.pdf JESDataPrescale60.pdf
./RunGraph 7 N NONE SD7_Data; mv JESCheck.pdf JESData.pdf
# ./RunGraph 7 N 100 SD7_DataPrescale_100; mv JESCheck.pdf JESDataPrescale100.pdf
./RunGraph 7 N 80 SD7_DataPrescale_80; mv JESCheck.pdf JESDataPrescale80.pdf
./RunGraph 7 N 60 SD7_DataPrescale_60; mv JESCheck.pdf JESDataPrescale60.pdf

CompileRootMacro PickGraphs.cpp RunPickGraph

./RunPickGraph 0
./RunPickGraph 7

CompileRootMacro CenterGraphs.cpp RunCenterGraph

./RunCenterGraph 0
./RunCenterGraph 7

CompileRootMacro MakeProjection.cpp RunProjection

./RunProjection 0
./RunProjection 7

CompileRootMacro MakeSummaryPlotsPostApproval.cpp RunSummary

./RunSummary
 

