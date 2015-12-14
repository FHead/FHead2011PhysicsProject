WorkspaceBase=~/work/PhysicsWorkspace/HiggsProperties/
g++ FitClass.cpp -o FitClass.o -c -I $WorkspaceBase/CommonCode/include \
   `root-config --glibs` `root-config --cflags` \
   -I $HOME/RootMacros
g++ DoFit.cpp -o PerformFits \
   `root-config --glibs` `root-config --cflags` \
   -I $WorkspaceBase/CommonCode/include \
   $WorkspaceBase/CommonCode/library/Lists.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   -I $HOME/RootMacros $HOME/RootMacros/Code/library/*.o \
   FitClass.o

