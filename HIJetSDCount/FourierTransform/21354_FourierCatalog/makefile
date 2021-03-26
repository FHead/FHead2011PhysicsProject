default: TestRun

FTHelper.o: FTHelper.cpp FTHelper.h
	g++ FTHelper.cpp -c -o FTHelper.o

Execute: FourierTransform.cpp FTHelper.o
	CompileRootMacro FourierTransform.cpp Execute FTHelper.o

TestRun: Execute
	./Execute --N 89 --Size 0.017 --Output FourierCatalog10.pdf --Truncation 10
	./Execute --N 89 --Size 0.017 --Output FourierCatalog20.pdf --Truncation 20
	cp FourierCatalog*.pdf ~/public/html


