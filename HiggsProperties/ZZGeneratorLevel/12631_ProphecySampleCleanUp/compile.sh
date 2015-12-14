WorkspaceBase=$HOME/PhysicsWorkspace/HiggsProperties/
g++ LeptonResponse.cpp -I$HOME/RootMacros -I$WorkspaceBase/CommonCode/include \
   -O3 -g -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$HOME/RootMacros -I$WorkspaceBase/CommonCode/include \
   -O3 -g -c -o PTYFunctions.o
g++ ConvertToTree.cpp -I$HOME/RootMacros -I$WorkspaceBase/CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/CalculateME_*.o \
   `root-config --glibs` `root-config --cflags` \
   LeptonResponse.o PTYFunctions.o \
   -O3 -g -o ProcessLHE
