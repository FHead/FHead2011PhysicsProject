default: TestRun

Execute: FourierTransform.cpp
	CompileRootMacro FourierTransform.cpp Execute

TestRun: Execute
	./Execute --Input Samples/JetTree_0.root --Output FourierTransformFirstTry.pdf --Percentage 0.05 --DoIndividual true
	cp FourierTransformFirstTry.pdf ~/public/html/
