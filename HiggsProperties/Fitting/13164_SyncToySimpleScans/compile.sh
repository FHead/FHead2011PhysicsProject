# Home=/home/yichen
Home=$HOME
WorkspaceBase=$Home/work/PhysicsWorkspace/HiggsProperties

# echo Compiling PlotYieldFraction
# g++ PlotYieldFraction.cpp -o PlotYieldFraction \
#    -I ../../CommonCode/include `root-config --cflags` `root-config --glibs` -I$Home/RootMacros
echo Compiling FitClass.o
g++ FitClass.cpp -o FitClass.o -c -I$WorkspaceBase/CommonCode/include `root-config --cflags` -I$Home/RootMacros -g
echo Compiling M4lSpectrum.o
g++ M4lSpectrum.cpp -o M4lSpectrum.o -c -I$WorkspaceBase/CommonCode/include `root-config --cflags` -I$Home/RootMacros -g
# echo Compiling MeasureNormalization
# g++ MeasureNormalization.cpp -o MeasureNormalization \
#    -I$WorkspaceBase/CommonCode/include `root-config --cflags` -I$Home/RootMacros \
#    $Home/RootMacros/Code/library/* \
#    M4lSpectrum.o -g
# echo Compiling PerformFits
# g++ DoFit.cpp `root-config --glibs` `root-config --cflags` -o PerformFits \
#    -I$WorkspaceBase/CommonCode/include/ $WorkspaceBase/CommonCode/library/AngleConversion.o \
#    -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o $WorkspaceBase/CommonCode/library/Lists.o \
#    M4lSpectrum.o -g
echo Compiling RunLikelihood
g++ Likelihood.cpp `root-config --glibs` `root-config --cflags` -o RunLikelihood \
   -I$WorkspaceBase/CommonCode/include/ $WorkspaceBase/CommonCode/library/AngleConversion.o \
   -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o $WorkspaceBase/CommonCode/library/Lists.o \
   M4lSpectrum.o -g
echo Compiling RunLikelihoodLambda1
# g++ LikelihoodLambda1.cpp `root-config --glibs` `root-config --cflags` -o RunLikelihoodLambda1 \
#    -I$WorkspaceBase/CommonCode/include/ $WorkspaceBase/CommonCode/library/AngleConversion.o \
#    -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o $WorkspaceBase/CommonCode/library/Lists.o \
#    M4lSpectrum.o -g
# echo Compiling RunLikelihoodA2ZA
# g++ LikelihoodA2ZA.cpp `root-config --glibs` `root-config --cflags` -o RunLikelihoodA2ZA \
#    -I$WorkspaceBase/CommonCode/include/ $WorkspaceBase/CommonCode/library/AngleConversion.o \
#    -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o $WorkspaceBase/CommonCode/library/Lists.o \
#    M4lSpectrum.o -g
echo Compiling RunLikelihoodA3ZA
g++ LikelihoodA3ZA.cpp `root-config --glibs` `root-config --cflags` -o RunLikelihoodA3ZA \
   -I$WorkspaceBase/CommonCode/include/ $WorkspaceBase/CommonCode/library/AngleConversion.o \
   -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o $WorkspaceBase/CommonCode/library/Lists.o \
   M4lSpectrum.o -g
echo Compiling RunLikelihoodA2AA
g++ LikelihoodA2AA.cpp `root-config --glibs` `root-config --cflags` -o RunLikelihoodA2AA \
   -I$WorkspaceBase/CommonCode/include/ $WorkspaceBase/CommonCode/library/AngleConversion.o \
   -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o $WorkspaceBase/CommonCode/library/Lists.o \
   M4lSpectrum.o -g
echo Compiling RunLikelihoodA3AA
g++ LikelihoodA3AA.cpp `root-config --glibs` `root-config --cflags` -o RunLikelihoodA3AA \
   -I$WorkspaceBase/CommonCode/include/ $WorkspaceBase/CommonCode/library/AngleConversion.o \
   -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o $WorkspaceBase/CommonCode/library/Lists.o \
   M4lSpectrum.o -g
