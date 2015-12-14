g++ ConvertVectorsToAnglesRoberto.cpp -o ConvertVectorsToAnglesRoberto \
   -I$HOME/PhysicsWorkspace/HiggsProperties/CommonCode/include \
   -I$HOME/RootMacros \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/AngleConversion.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o

g++ ConvertXYZToVectors.cpp -o ConvertXYZToVectors \
   -I$HOME/PhysicsWorkspace/HiggsProperties/CommonCode/include \
   -I$HOME/RootMacros \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/AngleConversion.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o


