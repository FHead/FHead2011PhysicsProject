default: RunLikelihood;

HybridCalculatorWithZPrime.o: HybridCalculatorWithZPrime.cpp HybridCalculatorWithZPrime.h
	CompileRootMacro HybridCalculatorWithZPrime.cpp HybridCalculatorWithZPrime.o -std=c++11 -c -I../../CommonCode/include

LeptonResponse.o: LeptonResponse.cpp LeptonResponse.h
	CompileRootMacro LeptonResponse.cpp LeptonResponse.o -std=c++11 -c -I../../CommonCode/include

PTYFunctions.o: PTYFunctions.cpp PTYFunctions.h
	CompileRootMacro PTYFunctions.cpp PTYFunctions.o -std=c++11 -c -I../../CommonCode/include

Likelihood.o: Likelihood.cpp Likelihood.h
	CompileRootMacro Likelihood.cpp Likelihood.o -std=c++11 -c -I../../CommonCode/include

ReducedLikelihood.o: ReducedLikelihood.cpp ReducedLikelihood.h
	CompileRootMacro ReducedLikelihood.cpp ReducedLikelihood.o -std=c++11 -c -I../../CommonCode/include

FitClass.o: FitClass.cpp FitClass.h
	CompileRootMacro FitClass.cpp FitClass.o -std=c++11 -c -I../../CommonCode/include

RunLikelihood: EvaluateLikelihood.cpp Likelihood.o ReducedLikelihood.o FitClass.o HybridCalculatorWithZPrime.o LeptonResponse.o PTYFunctions.o
	CompileRootMacro EvaluateLikelihood.cpp RunLikelihood -std=c++11 \
	-I ../../CommonCode/include \
   ../../CommonCode/library/Cuts.o \
   ../../CommonCode/library/Lists.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/EFTBases.o \
   ../../CommonCode/library/InterpretCoefficient.o \
   ../../CommonCode/library/FunctionLists.o \
   ../../CommonCode/library/MEFunctions.o \
   ../../CommonCode/library/CalculateME_Part*.o \
   ../../CommonCode/library/VolumeElement.o \
   Likelihood.o ReducedLikelihood.o FitClass.o HybridCalculatorWithZPrime.o LeptonResponse.o PTYFunctions.o

DoHarvest: Harvesting.cpp
	CompileRootMacro Harvesting.cpp DoHarvest

RunDiscriminantPlot: MakeDiscriminantPlot.cpp
	CompileRootMacro MakeDiscriminantPlot.cpp RunDiscriminantPlot
	./RunDiscriminantPlot

all: RunLikelihood DoHarvest
