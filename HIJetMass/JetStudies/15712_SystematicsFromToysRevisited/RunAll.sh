# CompileRootMacro EstimateSystematics.cpp
# ./a.out ScaledResult1PP6Dijet.root ScaledResult16PP6Dijet.root Ghost 0.07 0.17
# ./a.out ScaledResult1PP6Dijet.root ScaledResult9PP6Dijet.root Rho 0.07 0.17
# ./a.out ScaledResult1PP6Dijet.root ScaledResult13PP6Dijet.root Range 0.07 0.17
# ./a.out ScaledResult13PP6Dijet.root ScaledResult17PP6Dijet.root Range2 0.07 0.17
# ./a.out ScaledResult1PP6Dijet.root ScaledResult2PP6Dijet.root MB 0.07 0.17
# ./a.out ScaledResult1PP6Dijet.root ScaledResult6PP6Dijet.root Smear 0.07 0.17
# 
# CompileRootMacro EstimateSystematicsPT.cpp
# ./a.out ScaledResult1PP6Dijet.root ScaledResult1PP6Dijet.root PTScale 0.07 0.17
# 
# CompileRootMacro EstimateSystematicsEta.cpp
# ./a.out ScaledResult1PP6Dijet.root ScaledResult1PP6Dijet.root JetEta 0.05 0.20
# 
# CompileRootMacro EstimateSystematicsJER.cpp
# ./a.out ScaledResult1PP6Dijet.root ScaledResult1PP6Dijet.root JER 0.05 0.20
# 
# CompileRootMacro EstimateSystematicsSmear.cpp
# ./a.out ScaledResult1PP6Dijet.root ScaledResult1PP6Dijet.root NewSmear 0.07 0.17
# 
# CompileRootMacro EstimateSystematicsClosure.cpp
# ./a.out ScaledResult1PP8Dijet.root Straight/AA8Dijet.root Closure
# ./a.out ScaledResult13PP8Dijet.root Straight/AA8Dijet.root Closure2

CompileRootMacro EstimateSystematics.cpp
./a.out ScaledResult1PP6Dijet.root  ScaledResult16PP6Dijet.root Normal Ghost    0.07 0.17
./a.out ScaledResult1PP6Dijet.root  ScaledResult9PP6Dijet.root  Normal Rho      0.07 0.17
./a.out ScaledResult1PP6Dijet.root  ScaledResult13PP6Dijet.root Normal Range    0.07 0.17
./a.out ScaledResult13PP6Dijet.root ScaledResult17PP6Dijet.root Normal Range2   0.07 0.17
./a.out ScaledResult1PP6Dijet.root  ScaledResult2PP6Dijet.root  Normal MB       0.07 0.17
./a.out ScaledResult1PP6Dijet.root  ScaledResult6PP6Dijet.root  Normal Smear    0.07 0.17
./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  PT     PTScale  0.07 0.17
./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  Eta    JetEta   0.05 0.20
./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  JER    JER      0.05 0.20
./a.out ScaledResult1PP6Dijet.root  ScaledResult1PP6Dijet.root  Smear  NewSmear 0.07 0.17

