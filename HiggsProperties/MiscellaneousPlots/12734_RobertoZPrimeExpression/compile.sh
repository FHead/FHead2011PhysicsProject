g++ PTYFunctions.cpp \
   -c -o PTYFunctions.o
g++ GenerateSamples.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/VolumeElement.o \
   ../../CommonCode/library/CalculateME_Part*.o \
   ../../CommonCode/library/MEFunctions.o \
   PTYFunctions.o \
   -O3 \
   -o Run
g++ Synthesize.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   -O3 \
   -o Synthesize
g++ ConvertToTree.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   ../../CommonCode/library/AngleConversion.o \
   `root-config --glibs` `root-config --cflags` \
   -O3 -o ConvertToTree


