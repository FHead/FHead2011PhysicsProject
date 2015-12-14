CompileRootMacro FitClass.cpp FitClass.o -c -I ../../CommonCode/include
CompileRootMacro DoFit.cpp PerformFits \
   -I ../../CommonCode/include ../../CommonCode/library/*ZAME_Part2.o \
   ../../CommonCode/library/AngleConversion.o \
   ~/RootMacros/Code/library/TauHelperFunctions2.o \
   ~/RootMacros/Code/library/DrawRandom.o \
   FitClass.o

