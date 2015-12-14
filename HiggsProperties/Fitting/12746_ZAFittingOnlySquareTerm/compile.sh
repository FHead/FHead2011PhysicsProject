CompileRootMacro FitClass.cpp FitClass.o -c -I ../../CommonCode/include
CompileRootMacro DoFit.cpp PerformFits \
   -I ../../CommonCode/include ../../CommonCode/library/* \
   FitClass.o

