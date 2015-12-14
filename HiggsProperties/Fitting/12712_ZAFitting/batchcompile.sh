Base=$1
g++ $Base/FitClass.cpp -o FitClass.o -c -I $Base/../../CommonCode/include \
   `root-config --glibs` `root-config --cflags` \
   -I $HOME/RootMacros $HOME/RootMacros/Code/library/*.o
g++ $Base/DoFit.cpp -o PerformFits \
   `root-config --glibs` `root-config --cflags` \
   -I $Base/../../CommonCode/include $Base/../../CommonCode/library/* \
   -I $HOME/RootMacros $HOME/RootMacros/Code/library/*.o \
   FitClass.o

