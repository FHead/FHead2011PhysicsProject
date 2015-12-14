g++ ZAHybridCalculator.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   -O3 -c -o ZAHybridCalculator.o
g++ LeptonResponse.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   -O3 -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   -O3 -c -o PTYFunctions.o
g++ MakeToys.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/VolumeElement.o \
   ../../CommonCode/library/CalculateME_Part*.o \
   ../../CommonCode/library/CalculateZAME_Part*.o \
   ../../CommonCode/library/MEFunctions.o \
   -O3 \
   ZAHybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -o Run
g++ ConvertToTree.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   ../../CommonCode/library/AngleConversion.o \
   `root-config --glibs` `root-config --cflags` \
   -O3 -o ConvertToTree


