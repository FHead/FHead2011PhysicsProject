g++ ConvertVectorsToAnglesRoberto.cpp -o ConvertVectorsToAnglesRoberto \
   -I$PhysicsWorkspace/HiggsProperties/CommonCode/include \
   -I$RootMacrosBase \
   $PhysicsWorkspace/HiggsProperties/CommonCode/library/AngleConversion.o \
   $RootMacrosBase/Code/library/TauHelperFunctions3.o

g++ ConvertXYZToVectors.cpp -o ConvertXYZToVectors \
   -I$PhysicsWorkspace/HiggsProperties/CommonCode/include \
   -I$RootMacrosBase \
   $PhysicsWorkspace/HiggsProperties/CommonCode/library/AngleConversion.o \
   $RootMacrosBase/Code/library/TauHelperFunctions3.o


