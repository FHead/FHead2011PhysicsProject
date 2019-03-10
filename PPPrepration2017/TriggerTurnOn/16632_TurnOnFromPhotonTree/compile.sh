g++ TurnOnCurves.cpp -o a.out -std=c++1y \
   `root-config --glibs --cflags` \
   -I../../CommonCode/include ../../CommonCode/library/*.o \
   -I$RootMacrosBase/Code/include $RootMacrosBase/Code/library/*.o
