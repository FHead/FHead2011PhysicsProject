CompileRootMacro ReadTree.cpp ReadTree.o -c | grep -v warning
CompileRootMacro JetEnergyScale.cpp JetEnergyScale.o -c | grep -v warning
CompileRootMacro MakeGraphs.cpp RunGraph ReadTree.o JetEnergyScale.o

./RunGraph PP6Dijet.root 0 Y 100 SD0_PP6
./RunGraph PP8Dijet.root 0 Y 100 SD0_PP8
./RunGraph PPHerwig.root 0 Y 100 SD0_PPHerwig
./RunGraph PPDataHighPTJet.root 0 N Dummy SD0_Data
./RunGraph PP6Dijet.root 7 Y 100 SD7_PP6
./RunGraph PP8Dijet.root 7 Y 100 SD7_PP8
./RunGraph PPHerwig.root 7 Y 100 SD7_PPHerwig
./RunGraph PPDataHighPTJet.root 7 N Dummy SD7_Data

CompileRootMacro PickGraphs.cpp RunPickGraph

./RunPickGraph 0
./RunPickGraph 7

CompileRootMacro MakeSummaryPlots.cpp RunSummary

./RunSummary

mkdir -p PDFPlots

mv Plots/*pdf PDFPlots/

# pdflatex QuickView
