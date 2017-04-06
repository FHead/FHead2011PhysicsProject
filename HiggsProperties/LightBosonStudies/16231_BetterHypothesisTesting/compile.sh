CompileRootMacro Likelihood.cpp Likelihood.o -std=c++11 -c \
   -I../../CommonCode/include
CompileRootMacro ReducedLikelihood.cpp ReducedLikelihood.o -std=c++11 -c \
   -I../../CommonCode/include
CompileRootMacro FitClass.cpp FitClass.o -std=c++11 -c \
   -I../../CommonCode/include
CompileRootMacro EvaluateLikelihood.cpp RunLikelihood -std=c++11 \
   -I ../../CommonCode/include \
   ../../CommonCode/library/Cuts.o \
   ../../CommonCode/library/Lists.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/EFTBases.o \
   ../../CommonCode/library/InterpretCoefficient.o \
   Likelihood.o ReducedLikelihood.o FitClass.o
