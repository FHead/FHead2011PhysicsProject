Home=/afs/cern.ch/user/c/chenyi/
# Home=$HOME
WorkspaceBase=$Home/work/PhysicsWorkspace/HiggsProperties

# echo Compiling PlotYieldFraction
# g++ PlotYieldFraction.cpp -o PlotYieldFraction \
#    -I ../../CommonCode/include `root-config --cflags` `root-config --glibs` -I$Home/RootMacros
echo Compiling FitClass.o
g++ FitClass.cpp -o FitClass.o -c -I$WorkspaceBase/CommonCode/include `root-config --cflags` -I$Home/RootMacros -g
echo Compiling FitClass1000.o
g++ FitClass1000.cpp -o FitClass1000.o -c -I$WorkspaceBase/CommonCode/include `root-config --cflags` -I$Home/RootMacros -g
echo Compiling FileIO.o
g++ FileIO.cpp -o FileIO.o -c -I$WorkspaceBase/CommonCode/include `root-config --cflags` -I$Home/RootMacros -g
echo Compiling M4lSpectrum.o
g++ M4lSpectrum.cpp -o M4lSpectrum.o -c -I$WorkspaceBase/CommonCode/include `root-config --cflags` -I$Home/RootMacros -g
# echo Compiling MeasureNormalization
# g++ MeasureNormalization.cpp -o MeasureNormalization \
#    -I$WorkspaceBase/CommonCode/include `root-config --cflags` -I$Home/RootMacros \
#    $Home/RootMacros/Code/library/* \
#    M4lSpectrum.o -g
echo Compiling PerformFits
g++ DoFit.cpp `root-config --glibs` `root-config --cflags` -o PerformFits \
   -I$WorkspaceBase/CommonCode/include/ $WorkspaceBase/CommonCode/library/AngleConversion.o \
   -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o $WorkspaceBase/CommonCode/library/Lists.o \
   M4lSpectrum.o FileIO.o -g
# echo Compiling PerformFitsEMMEMixedZX
# g++ DoFitEMMETogetherMixedZX.cpp `root-config --glibs` `root-config --cflags` -o PerformFitsMixedZX \
#    -I$WorkspaceBase/CommonCode/include/ $WorkspaceBase/CommonCode/library/AngleConversion.o \
#    -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o $WorkspaceBase/CommonCode/library/Lists.o \
#    M4lSpectrum.o FileIO.o -g




