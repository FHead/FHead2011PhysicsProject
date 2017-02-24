CompileRootMacro EstimateSystematics.cpp
for SD in 0 7
do
   # ./a.out ScaledResult1PP6Dijet.root  ScaledResult15PP6Dijet.root $SD Ghost  Ghost    0.07 0.17
   # ./a.out ScaledResult16PP6Dijet.root ScaledResult15PP6Dijet.root $SD Ghost  Ghost2   0.07 0.17
   # ./a.out ScaledResult1PP6Dijet.root  ScaledResult16PP6Dijet.root $SD Normal Ghost3   0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult9PP6Dijet.root  $SD Rho    Rho      0.07 0.17
   # ./a.out ScaledResult1PP6Dijet.root  ScaledResult13PP6Dijet.root $SD Normal Range    0.07 0.17
   # ./a.out ScaledResult13PP6Dijet.root ScaledResult17PP6Dijet.root $SD Normal Range2   0.07 0.17
   # ./a.out ScaledResult1PP6Dijet.root  ScaledResult2PP6Dijet.root  $SD Normal MB       0.07 0.17
   ./a.out ScaledResult1PP6Dijet.root  ScaledResult6PP6Dijet.root  $SD Normal Smear    0.07 0.17
   # ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD PT     PTScale  0.07 0.17
   # ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD Eta    JetEta   0.05 0.20
   # ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD JER    JER      0.05 0.20
   # ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD Smear  NewSmear 0.07 0.17
   # ./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  $SD DR     DR       0.20 0.35
done

CompileRootMacro CombineSystematics.cpp

./a.out 0 N
./a.out 7 N
