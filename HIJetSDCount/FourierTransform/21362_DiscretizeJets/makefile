default: FullRun

Execute: Discretize.cpp
	CompileRootMacro Discretize.cpp Execute

TestRun: Execute
	./Execute --input Input/JetTree_0.root --output Output/JetTree_0.root

FullRun: Execute
	for i in `ls Input/`; do ./Execute --input Input/$$i --output Output/$$i; done
