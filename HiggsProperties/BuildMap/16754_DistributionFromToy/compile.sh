WorkspaceBase=$PhysicsWorkspace/HiggsProperties
# g++ HybridCalculator.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
#    -pedantic -W -Wall -Wno-long-long \
#    -c -o HybridCalculator.o
g++ HybridCalculatorWithZPrime.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   -pedantic -W -Wall -Wno-long-long \
   -c -o HybridCalculatorWithZPrime.o
g++ LeptonResponse.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   -pedantic -W -Wall -Wno-long-long \
   -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   -pedantic -W -Wall -Wno-long-long \
   -c -o PTYFunctions.o
g++ MakeToys.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   $RootMacrosBase/Code/library/DrawRandom.o \
   $RootMacrosBase/Code/library/TauHelperFunctions3.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part*.o \
   $WorkspaceBase/CommonCode/library/VolumeElement.o \
   $WorkspaceBase/CommonCode/library/MEFunctions.o \
   $WorkspaceBase/CommonCode/library/FunctionLists.o \
   $WorkspaceBase/CommonCode/library/Cuts.o \
   $WorkspaceBase/CommonCode/library/Lists.o \
   HybridCalculatorWithZPrime.o LeptonResponse.o PTYFunctions.o \
   `root-config --libs` `root-config --cflags` \
   -pedantic -W -Wall -Wno-long-long \
   -o Run

CompileRootMacro DistributionPlots.cpp a.out -I../../CommonCode/include ../../CommonCode/library/AngleConversion.o

