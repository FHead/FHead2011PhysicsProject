cp CalculateBranch.cpp CalculateBranch_8TeV.cpp
cat CalculateBranch.cpp | sed "s/8TeV/7TeV/g" > CalculateBranch_7TeV.cpp
cp CalculateBranchBackground.cpp CalculateBranchBackground_8TeV.cpp
cat CalculateBranchBackground.cpp | sed "s/8TeV/7TeV/g" > CalculateBranchBackground_7TeV.cpp
cp CalculateBranchCoarse.cpp CalculateBranchCoarse_8TeV.cpp
cat CalculateBranchCoarse.cpp | sed "s/8TeV/7TeV/g" > CalculateBranchCoarse_7TeV.cpp
cp CalculateBranchBackgroundCoarse.cpp CalculateBranchBackgroundCoarse_8TeV.cpp
cat CalculateBranchBackgroundCoarse.cpp | sed "s/8TeV/7TeV/g" > CalculateBranchBackgroundCoarse_7TeV.cpp

g++ HybridCalculator.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   `root-config --cflags` -O3 -c -o HybridCalculator.o
g++ LeptonResponse.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   `root-config --cflags` -O3 -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   `root-config --cflags` -O3 -c -o PTYFunctions.o
g++ CalculateBranch_7TeV.cpp -I$HOME/RootMacros -I../../CommonCode/include \
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
   -o RunSignal7TeV
g++ CalculateBranch_8TeV.cpp -I$HOME/RootMacros -I../../CommonCode/include \
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
   -o RunSignal8TeV
g++ CalculateBranchBackground_7TeV.cpp -I$HOME/RootMacros -I../../CommonCode/include \
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
   -o RunBackground7TeV
g++ CalculateBranchBackground_8TeV.cpp -I$HOME/RootMacros -I../../CommonCode/include \
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
   -o RunBackground8TeV
g++ CalculateBranchBackgroundCoarse_7TeV.cpp -I$HOME/RootMacros -I../../CommonCode/include \
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
   -o RunBackground7TeVCoarse
g++ CalculateBranchBackgroundCoarse_8TeV.cpp -I$HOME/RootMacros -I../../CommonCode/include \
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
   -o RunBackground8TeVCoarse
g++ CalculateBranchCoarse_7TeV.cpp -I$HOME/RootMacros -I../../CommonCode/include \
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
   -o Run7TeVCoarse
g++ CalculateBranchCoarse_8TeV.cpp -I$HOME/RootMacros -I../../CommonCode/include \
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
   -o Run8TeVCoarse








