Home=/home/yichen/
WorkspaceBase=$Home/PhysicsWorkspace/HiggsProperties
CompileRootMacro MakeComparison.cpp Run \
   -I$WorkspaceBase/CommonCode/include \
   $WorkspaceBase/CommonCode/library/AngleConversion.o \
   $WorkspaceBase/CommonCode/library/Cuts.o \
   -pedantic -W -Wall -Wno-long-long


