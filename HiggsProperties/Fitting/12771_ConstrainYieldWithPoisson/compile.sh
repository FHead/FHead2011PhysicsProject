g++ FitClass.cpp -g -o FitClass.o -c -I ../../CommonCode/include `root-config --cflags` -I$HOME/RootMacros
g++ DoFit.cpp -g `root-config --glibs` `root-config --cflags` -o PerformFits -I ../../CommonCode/include/ ../../CommonCode/library/AngleConversion.o -I$HOME/RootMacros $HOME/RootMacros/Code/library/* FitClass.o ../../CommonCode/library/Lists.o
