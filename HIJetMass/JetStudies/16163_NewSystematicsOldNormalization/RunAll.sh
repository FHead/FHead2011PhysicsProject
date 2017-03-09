CompileRootMacro EstimateSystematics.cpp
for SD in 0 7
do
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult15PP6Dijet.root $SD Ghost  Ghost    0.07 0.17
   ./a.out ScaledResult16PP6Dijet.root ScaledResult15PP6Dijet.root $SD Ghost  Ghost2   0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult16PP6Dijet.root $SD Normal Ghost3   0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult9PP6Dijet.root  $SD Rho    Rho      0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult13PP6Dijet.root $SD Normal Range    0.07 0.17
   ./a.out ScaledResult13PP6Dijet.root ScaledResult17PP6Dijet.root $SD Normal Range2   0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult2PP6Dijet.root  $SD Normal MB       0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult6PP6Dijet.root  $SD Normal Smear    0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD PT     PTScale  0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD Eta    JetEta   0.05 0.20
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD JER    JER      0.05 0.20
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD Smear  NewSmear 0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD DR     DR       0.20 0.35
done

CompileRootMacro MakeFlatGraphs.cpp

./a.out OutputFile_Trigger_0.root 0.05
./a.out OutputFile_Trigger_7.root 0.05
./a.out OutputFile_GluonQuark_0.root 0.07
./a.out OutputFile_GluonQuark_7.root 0.07

CompileRootMacro CombineSystematics.cpp

./a.out 0 N
./a.out 7 N
./a.out 0 Y
./a.out 7 Y

CompileRootMacro PrettySystematicsPlot.cpp

for SD in 0 7
do
   for iC in `seq 0 3`
   do
      for iPT in `seq 1 5`
      do
         ./a.out C${iC}_P${iPT} $SD
      done
   done
done






