WorkspaceBase=$HOME/PhysicsWorkspace/HiggsProperties
g++ HybridCalculator.cpp -I$HOME/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -Os -c -o HybridCalculator.o
g++ LeptonResponse.cpp -I$HOME/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -Os -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$HOME/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -Os -c -o PTYFunctions.o
g++ CalculateBranch.cpp -I$HOME/RootMacros -I$WorkspaceBase/CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/CalculateME_*.o \
   $WorkspaceBase/CommonCode/library/MEFunctions.o \
   $WorkspaceBase/CommonCode/library/VolumeElement.o \
   `root-config --glibs` `root-config --cflags` -Os \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -o RunLikelihood


