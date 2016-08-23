Home=/home/yichen/
WorkspaceBase=$Home/PhysicsWorkspace/HiggsProperties
g++ HybridCalculator.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   -pedantic -W -Wall -Wno-long-long \
   -c -o HybridCalculator.o
g++ LeptonResponse.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   -pedantic -W -Wall -Wno-long-long \
   -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   -pedantic -W -Wall -Wno-long-long \
   -c -o PTYFunctions.o
g++ MakeToys.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   $Home/RootMacros/Code/library/DrawRandom.o \
   $Home/RootMacros/Code/library/TauHelperFunctions2.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part*.o \
   $WorkspaceBase/CommonCode/library/VolumeElement.o \
   $WorkspaceBase/CommonCode/library/MEFunctions.o \
   $WorkspaceBase/CommonCode/library/Cuts.o \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -pedantic -W -Wall -Wno-long-long \
   -o Run


