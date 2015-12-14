g++ HybridCalculator.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   `root-config --cflags` -O3 -c -o HybridCalculator.o
g++ LeptonResponse.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   `root-config --cflags` -O3 -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   `root-config --cflags` -O3 -c -o PTYFunctions.o
g++ CalculateBranch.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/CalculateME_Part1.o \
   ../../CommonCode/library/CalculateME_Part3.o \
   ../../CommonCode/library/CalculateME_Part7.o \
   ../../CommonCode/library/CalculateME_Part12.o \
   ../../CommonCode/library/CalculateME_Part14.o \
   ../../CommonCode/library/MEFunctions.o \
   ../../CommonCode/library/VolumeElement.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -o RunSignal
g++ CalculateBranchBackground.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/CalculateME_Part1.o \
   ../../CommonCode/library/CalculateME_Part3.o \
   ../../CommonCode/library/CalculateME_Part7.o \
   ../../CommonCode/library/CalculateME_Part12.o \
   ../../CommonCode/library/CalculateME_Part14.o \
   ../../CommonCode/library/MEFunctions.o \
   ../../CommonCode/library/VolumeElement.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -o RunBackground
g++ CalculateBranchBackgroundCapital.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/CalculateME_Part1.o \
   ../../CommonCode/library/CalculateME_Part3.o \
   ../../CommonCode/library/CalculateME_Part7.o \
   ../../CommonCode/library/CalculateME_Part12.o \
   ../../CommonCode/library/CalculateME_Part14.o \
   ../../CommonCode/library/MEFunctions.o \
   ../../CommonCode/library/VolumeElement.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -o RunBackgroundCapital


