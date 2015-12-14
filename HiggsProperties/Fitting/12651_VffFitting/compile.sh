WorkspaceBase=~/PhysicsWorkspace/HiggsProperties/
g++ FitClass.cpp -o FitClass.o -c -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` \
   -I$HOME/RootMacros
g++ DoFit.cpp -o PerformFits \
   -I$WorkspaceBase/CommonCode/include $WorkspaceBase/CommonCode/library/AngleConversion.o \
   -I$HOME/RootMacros $HOME/RootMacros/Code/library/* \
   `root-config --cflags` `root-config --glibs` \
   FitClass.o

