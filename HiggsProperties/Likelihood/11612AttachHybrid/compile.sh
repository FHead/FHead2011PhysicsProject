g++ HybridCalculator.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   `root-config --cflags` -O3 -c -o HybridCalculator.o
g++ LeptonResponse.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   `root-config --cflags` -O3 -c -o LeptonResponse.o
g++ AttachLikelihood.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   /home/yichen/RootMacros/Code/library/DrawRandom.o \
   /home/yichen/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/CalculateME.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   HybridCalculator.o LeptonResponse.o \
   -o Run


