Home=/home/yichen
WorkspaceBase=/home/yichen/PhysicsWorkspace/HiggsProperties/
g++ HybridCalculator.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   -g `root-config --cflags` -O3 -c -o HybridCalculator.o
g++ HybridCalculatorWithZPrime.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   -g `root-config --cflags` -O3 -c -o HybridCalculatorWithZPrime.o
g++ LeptonResponse.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   -g `root-config --cflags` -O3 -c -o LeptonResponse.o
g++ PTYFunctions.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   -g `root-config --cflags` -O3 -c -o PTYFunctions.o
g++ StockM4l.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   -g `root-config --cflags` -O3 -c -o StockM4l.o
g++ CalculateBranch.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   $RootMacrosBase/Code/library/DrawRandom2.o \
   $RootMacrosBase/Code/library/TauHelperFunctions3.o \
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
   $WorkspaceBase/CommonCode/library/CalculateME_Part30.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part31.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part32.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part33.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part34.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part35.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part36.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part37.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part38.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part39.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part40.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part41.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part42.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part43.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part44.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part45.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part46.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part47.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part48.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part49.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part50.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part51.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part52.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part53.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part54.o \
   $WorkspaceBase/CommonCode/library/MEFunctions.o \
   $WorkspaceBase/CommonCode/library/VolumeElement.o \
   $WorkspaceBase/CommonCode/library/Lists.o \
   `root-config --glibs` `root-config --cflags` -O3 \
   -g HybridCalculatorWithZPrime.o LeptonResponse.o PTYFunctions.o StockM4l.o \
   -o RunSignal
g++ CalculateBranchBackground.cpp -I$RootMacrosBase -I$WorkspaceBase/CommonCode/include \
   $RootMacrosBase/Code/library/DrawRandom2.o \
   $RootMacrosBase/Code/library/TauHelperFunctions3.o \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part1.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part3.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part6.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part7.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part12.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part14.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part30.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part31.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part32.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part33.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part34.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part35.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part36.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part37.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part38.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part39.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part40.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part41.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part42.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part43.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part44.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part45.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part46.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part47.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part48.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part49.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part50.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part51.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part52.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part53.o \
   $WorkspaceBase/CommonCode/library/CalculateME_Part54.o \
   $WorkspaceBase/CommonCode/library/MEFunctions.o \
   $WorkspaceBase/CommonCode/library/VolumeElement.o \
   $WorkspaceBase/CommonCode/library/Constants.o \
   -g `root-config --glibs` `root-config --cflags` -O3 \
   HybridCalculator.o LeptonResponse.o PTYFunctions.o StockM4l.o \
   -o RunBackground
g++ AttachBranches.cpp -I$RootMacrosBase \
   -g `root-config --glibs` `root-config --cflags` -O3 \
   -o AttachBranch

