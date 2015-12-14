g++ FitClass.cpp -o FitClass.o -c -I ../../../../CommonCode/include \
   `root-config --glibs` `root-config --cflags` \
   -I $HOME/RootMacros $HOME/RootMacros/Code/library/*.o
g++ DoFit.cpp -o PerformFits -g \
   `root-config --glibs` `root-config --cflags` \
   -I ../../../../CommonCode/include ../../../../CommonCode/library/* \
   -I $HOME/RootMacros $HOME/RootMacros/Code/library/*.o \
   FitClass.o

