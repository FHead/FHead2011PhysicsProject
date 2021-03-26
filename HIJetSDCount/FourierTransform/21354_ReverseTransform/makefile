default: FirstTry

FTHelper.o: FTHelper.cpp FTHelper.h
	g++ FTHelper.cpp -c -o FTHelper.o

Execute: FourierTransform.cpp FTHelper.o
	CompileRootMacro FourierTransform.cpp Execute FTHelper.o

TestRun: FTHelper.o TestFTHelper.cpp
	CompileRootMacro TestFTHelper.cpp TestRun FTHelper.o
	./TestRun
	cp TestRun.pdf ~/public/html

FirstTry: Execute
	./Execute --Input NewSamples/JetTree_0.root --Output FourierTransformFirstTry.pdf \
		--Percentage 0.1 --DoIndividual true --MinS 100
	cp FourierTransformFirstTry.pdf ~/public/html/
