Base=$1
g++ $Base/ProcessSample.cpp -o DoCut \
   `root-config --glibs` `root-config --cflags` \
   -I $Base/../../CommonCode/include $Base/../../CommonCode/library/AngleConversion.o \
   -I $HOME/RootMacros $HOME/RootMacros/Code/library/*.o

