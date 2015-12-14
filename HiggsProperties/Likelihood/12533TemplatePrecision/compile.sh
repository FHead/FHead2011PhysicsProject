g++ PTYFunctions.cpp -c -o PTYFunctions.o
g++ AttachEfficiency.cpp -o AttachEfficiency \
   -I$HOME/RootMacros -I../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../CommonCode/library/AngleConversion.o \
   `root-config --glibs` `root-config --cflags` \
   PTYFunctions.o

