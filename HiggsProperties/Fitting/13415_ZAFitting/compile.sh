g++ FitClass.cpp -o FitClass.o -c -I $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/include \
   -I$HOME/RootMacros \
   `root-config --cflags`
g++ DoFit.cpp -o PerformFits \
   `root-config --cflags` `root-config --glibs` \
   -I$HOME/RootMacros \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   -I$HOME/PhysicsWorkspace/HiggsProperties/CommonCode/include \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/*ZAME_Part2.o \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/AngleConversion.o \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/Lists.o \
   FitClass.o

