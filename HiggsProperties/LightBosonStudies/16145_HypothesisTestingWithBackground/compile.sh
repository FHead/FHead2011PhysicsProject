CompileRootMacro Likelihood.cpp Likelihood.o -std=c++11 -c \
   -I../../CommonCode/include
CompileRootMacro EvaluateLikelihood.cpp Run -std=c++11 \
   -I ../../CommonCode/include \
   ../../CommonCode/library/Cuts.o \
   ../../CommonCode/library/Lists.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/MEFunctions.o \
   ../../CommonCode/library/CalculateME_Part*.o \
   ../../CommonCode/library/EFTBases.o \
   ../../CommonCode/library/InterpretCoefficient.o \
   Likelihood.o
