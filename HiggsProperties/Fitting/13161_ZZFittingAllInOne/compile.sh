g++ FitClass.cpp -o FitClass.o -c -I $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/include \
   -I$HOME/RootMacros \
   `root-config --cflags`
g++ DoFit.cpp -o PerformFits \
   `root-config --cflags` `root-config --glibs` \
   -I$HOME/RootMacros \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   -I$HOME/PhysicsWorkspace/HiggsProperties/CommonCode/include \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/CalculateME_Part1.o \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/CalculateME_Part3.o \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/CalculateME_Part4.o \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/CalculateME_Part7.o \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/CalculateME_Part12.o \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/CalculateME_Part14.o \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/MEFunctions.o \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/AngleConversion.o \
   FitClass.o

