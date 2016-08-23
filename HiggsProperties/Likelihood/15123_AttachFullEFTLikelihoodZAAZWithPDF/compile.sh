Home=/home/yichen
WorkspaceBase=/home/yichen/PhysicsWorkspace/HiggsProperties/
g++ HybridCalculator.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -O3 -c -o HybridCalculator.o
g++ LeptonResponse.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -O3 -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -O3 -c -o PTYFunctions.o
g++ StockM4l.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` -O3 -c -o StockM4l.o
g++ CalculateBranch.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   $Home/RootMacros/Code/library/DrawRandom2.o \
   $Home/RootMacros/Code/library/TauHelperFunctions2.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part1.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part3.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part6.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part7.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part12.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part14.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part22.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part23.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part24.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part25.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part26.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part27.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part28.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part29.o \
   $WorkspaceBase/CommonCode/library/MEFunctions.o \
   $WorkspaceBase/CommonCode/library/VolumeElement.o \
   $WorkspaceBase/CommonCode/library/Lists.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o StockM4l.o \
   -o RunSignal
g++ CalculateBranchBackground.cpp -I$Home/RootMacros -I$WorkspaceBase/CommonCode/include \
   $Home/RootMacros/Code/library/DrawRandom2.o \
   $Home/RootMacros/Code/library/TauHelperFunctions2.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part1.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part3.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part6.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part7.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part12.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part14.o \
   $WorkspaceBase/CommonCode/library/MEFunctions.o \
   $WorkspaceBase/CommonCode/library/VolumeElement.o \
   $WorkspaceBase/CommonCode/library/Constants.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o StockM4l.o \
   -o RunBackground
g++ AttachBranches.cpp -I$Home/RootMacros \
   `root-config --glibs` `root-config --cflags` -O3 \
   -o AttachBranch

