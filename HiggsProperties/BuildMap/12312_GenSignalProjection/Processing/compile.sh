g++ MakeMatrixPlot.cpp -I$HOME/RootMacros -I../../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../../CommonCode/library/AngleConversion.o \
   ../../../CommonCode/library/VolumeElement.o \
   ../../../CommonCode/library/CalculateME_Part*.o \
   ../../../CommonCode/library/MEFunctions.o \
   `root-config --cflags` `root-config --glibs` \
   -O3 \
   -o RunMatrixPlot
g++ SortOutMatrixPlot.cpp -I$HOME/RootMacros -I../../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../../CommonCode/library/AngleConversion.o \
   ../../../CommonCode/library/VolumeElement.o \
   ../../../CommonCode/library/CalculateME_Part*.o \
   ../../../CommonCode/library/MEFunctions.o \
   `root-config --cflags` `root-config --glibs` \
   -O3 \
   -o RunSortOutMatrixPlot
# g++ MakePartialCrossSectionPlots.cpp -I$HOME/RootMacros -I../../../CommonCode/include \
#    $HOME/RootMacros/Code/library/DrawRandom.o \
#    $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
#    ../../../CommonCode/library/AngleConversion.o \
#    ../../../CommonCode/library/VolumeElement.o \
#    ../../../CommonCode/library/CalculateME_Part*.o \
#    ../../../CommonCode/library/MEFunctions.o \
#    `root-config --cflags` `root-config --glibs` \
#    -O3 \
#    -o RunPartialCrossSection
g++ SortOutPartialCrossSectionPlots.cpp -I$HOME/RootMacros -I../../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../../CommonCode/library/AngleConversion.o \
   ../../../CommonCode/library/VolumeElement.o \
   ../../../CommonCode/library/CalculateME_Part*.o \
   ../../../CommonCode/library/MEFunctions.o \
   `root-config --cflags` `root-config --glibs` \
   -O3 \
   -o RunSortOutPartialCrossSectionPlots
g++ MakeProjections.cpp -I$HOME/RootMacros -I../../../CommonCode/include \
   $HOME/RootMacros/Code/library/DrawRandom.o \
   $HOME/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../../CommonCode/library/AngleConversion.o \
   ../../../CommonCode/library/VolumeElement.o \
   ../../../CommonCode/library/CalculateME_Part*.o \
   ../../../CommonCode/library/MEFunctions.o \
   `root-config --cflags` `root-config --glibs` \
   -O3 \
   -o RunProjections

