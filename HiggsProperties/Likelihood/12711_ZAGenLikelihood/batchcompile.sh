Base=$1
g++ $Base/HybridCalculator.cpp -I$HOME/RootMacros -I$Base/../../CommonCode/include \
   `root-config --cflags` -O3 -c -o HybridCalculator.o
g++ $Base/LeptonResponse.cpp -I$HOME/RootMacros -I$Base/../../CommonCode/include \
   `root-config --cflags` -O3 -c -o LeptonResponse.o
g++ $Base/PTYFunctions.cpp -I$HOME/RootMacros -I$Base/../../CommonCode/include \
   `root-config --cflags` -O3 -c -o PTYFunctions.o
g++ $Base/CalculateBranch.cpp -I$HOME/RootMacros -I$Base/../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   $Base/../../CommonCode/library/AngleConversion.o \
   $Base/../../CommonCode/library/CalculateME_*.o \
   $Base/../../CommonCode/library/MEFunctions.o \
   $Base/../../CommonCode/library/VolumeElement.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -o RunSignal
g++ $Base/CalculateBranchBackground.cpp -I$HOME/RootMacros -I$Base/../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   $Base/../../CommonCode/library/AngleConversion.o \
   $Base/../../CommonCode/library/CalculateME_*.o \
   $Base/../../CommonCode/library/MEFunctions.o \
   $Base/../../CommonCode/library/VolumeElement.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -o RunBackground


