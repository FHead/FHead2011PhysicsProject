Home=/home/yichen
WorkspaceBase=/home/yichen/PhysicsWorkspace/HiggsProperties/
g++ ZAHybridCalculator.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -O3 -c -o ZAHybridCalculator.o
g++ LeptonResponse.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -O3 -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -O3 -c -o PTYFunctions.o
g++ CalculateBranch.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   $Home/RootMacros/Code/library/DrawRandom.o \
   $Home/RootMacros/Code/library/TauHelperFunctions2.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/CalculateZAME*.o \
   $WorkspaceBase/CommonCode/library/MEFunctionsZA.o \
   $WorkspaceBase/CommonCode/library/VolumeElement.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   ZAHybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -o RunSignal
g++ CalculateBranchBackground.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   $Home/RootMacros/Code/library/DrawRandom.o \
   $Home/RootMacros/Code/library/TauHelperFunctions2.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/CalculateZAME*.o \
   $WorkspaceBase/CommonCode/library/MEFunctionsZA.o \
   $WorkspaceBase/CommonCode/library/VolumeElement.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   ZAHybridCalculator.o LeptonResponse.o PTYFunctions.o \
   -o RunBackground
g++ AttachBranches.cpp -I$Home/RootMacros \
   `root-config --glibs` `root-config --cflags` -O3 \
   -o AttachBranch

