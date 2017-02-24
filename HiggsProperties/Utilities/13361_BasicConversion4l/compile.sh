g++ ConvertVectorsToAnglesRoberto.cpp -o ConvertVectorsToAnglesRoberto \
   -I$HOME/PhysicsWorkspace/HiggsProperties/CommonCode/include \
   -I$RootMacrosBase \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/AngleConversion.o \
   $RootMacrosBase/Code/library/TauHelperFunctions2.o

g++ ConvertXYZToVectors.cpp -o ConvertXYZToVectors \
   -I$HOME/PhysicsWorkspace/HiggsProperties/CommonCode/include \
   -I$RootMacrosBase \
   $HOME/PhysicsWorkspace/HiggsProperties/CommonCode/library/AngleConversion.o \
   $RootMacrosBase/Code/library/TauHelperFunctions2.o


