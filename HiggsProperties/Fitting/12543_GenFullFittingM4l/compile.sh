CommonCodeBase=$HOME/PhysicsWorkspace/HiggsProperties/CommonCode

g++ FitClass.cpp -o FitClass.o -c -I $CommonCodeBase/include \
   `root-config --glibs` `root-config --cflags` \
   -I $HOME/RootMacros $HOME/RootMacros/Code/library/*.o
g++ DoFit.cpp -o PerformFits -g \
   `root-config --glibs` `root-config --cflags` \
   -I $CommonCodeBase/include $CommonCodeBase/library/* \
   -I $HOME/RootMacros $HOME/RootMacros/Code/library/*.o \
   FitClass.o

