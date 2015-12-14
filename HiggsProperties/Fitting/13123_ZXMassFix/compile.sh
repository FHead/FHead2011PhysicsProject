g++ FitClass.cpp -o FitClass.o -c -I ../../CommonCode/include `root-config --cflags` -I$HOME/RootMacros
g++ M4lSpectrum.cpp -o M4lSpectrum.o -c -I ../../CommonCode/include `root-config --cflags` -I$HOME/RootMacros
g++ MeasureNormalization.cpp -o MeasureNormalization \
   -I ../../CommonCode/include `root-config --cflags` -I$HOME/RootMacros \
   $HOME/RootMacros/Code/library/* \
   M4lSpectrum.o
g++ DoFit.cpp `root-config --glibs` `root-config --cflags` -o PerformFits \
   -I../../CommonCode/include/ ../../CommonCode/library/AngleConversion.o \
   -I$HOME/RootMacros $HOME/RootMacros/Code/library/* FitClass.o ../../CommonCode/library/Lists.o \
   M4lSpectrum.o
