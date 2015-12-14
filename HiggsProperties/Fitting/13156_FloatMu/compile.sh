# Home=/home/yichen
Home=$HOME

echo Compiling PlotYieldFraction
g++ PlotYieldFraction.cpp -o PlotYieldFraction \
   -I ../../CommonCode/include `root-config --cflags` `root-config --glibs` -I$Home/RootMacros
echo Compiling FitClass.o
g++ FitClass.cpp -o FitClass.o -c -I ../../CommonCode/include `root-config --cflags` -I$Home/RootMacros
echo Compiling M4lSpectrum.o
g++ M4lSpectrum.cpp -o M4lSpectrum.o -c -I ../../CommonCode/include `root-config --cflags` -I$Home/RootMacros
echo Compiling MeasureNormalization
g++ MeasureNormalization.cpp -o MeasureNormalization \
   -I ../../CommonCode/include `root-config --cflags` -I$Home/RootMacros \
   $Home/RootMacros/Code/library/* \
   M4lSpectrum.o
echo Compiling PerformFits
g++ DoFit.cpp `root-config --glibs` `root-config --cflags` -o PerformFits \
   -I../../CommonCode/include/ ../../CommonCode/library/AngleConversion.o \
   -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o ../../CommonCode/library/Lists.o \
   M4lSpectrum.o 
# echo Compiling RunLikelihood
# g++ Likelihood.cpp `root-config --glibs` `root-config --cflags` -o RunLikelihood \
#    -I../../CommonCode/include/ ../../CommonCode/library/AngleConversion.o \
#    -I$Home/RootMacros $Home/RootMacros/Code/library/* FitClass.o ../../CommonCode/library/Lists.o \
#    M4lSpectrum.o
