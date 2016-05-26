Home=/home/yichen/
WorkspaceBase=$Home/PhysicsWorkspace/HiggsProperties/
g++ FitClass.cpp -o FitClass.o -c -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` \
   -g -I$Home/RootMacros
g++ StockM4l.cpp -o StockM4l.o -c -I$WorkspaceBase/CommonCode/include \
   `root-config --cflags` \
   -I$Home/RootMacros
g++ DoFit.cpp -o PerformFits \
   -I$WorkspaceBase/CommonCode/include $WorkspaceBase/CommonCode/library/AngleConversion.o \
   -I$Home/RootMacros $Home/RootMacros/Code/library/* \
   `root-config --cflags` `root-config --glibs` \
   $WorkspaceBase/CommonCode/library/Cuts.o \
   $WorkspaceBase/CommonCode/library/EFTBases.o \
   $WorkspaceBase/CommonCode/library/EFTPriors.o \
   $WorkspaceBase/CommonCode/library/Constants.o \
   $WorkspaceBase/CommonCode/library/InterpretCoefficient.o \
   -g FitClass.o StockM4l.o

