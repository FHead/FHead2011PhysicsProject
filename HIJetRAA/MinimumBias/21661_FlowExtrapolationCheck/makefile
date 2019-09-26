



default: TestRun

TestRun: Execute
	./Execute
	cp Output.pdf ~/public/html/

Execute: FlowCheck.cpp
	CompileRootMacro FlowCheck.cpp Execute

