CompileRootMacro FitClass.cpp FitClass.o -c -I ../../CommonCode/include
# CompileRootMacro DoFit.cpp PerformFits \
#    -I ../../CommonCode/include ../../CommonCode/library/* \
#    FitClass.o
g++ DoFit.cpp `root-config --glibs` `root-config --cflags` -o PerformFits -I ../../CommonCode/include/ ../../CommonCode/library/AngleConversion.o -I$HOME/RootMacros $HOME/RootMacros/Code/library/* FitClass.o ../../CommonCode/library/Lists.o
