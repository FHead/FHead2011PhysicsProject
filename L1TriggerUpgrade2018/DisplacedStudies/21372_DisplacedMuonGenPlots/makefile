default: TestRun

TestRun: Execute
	./Execute
	cp Output.pdf ~/public/html

Execute: MakeGenPlots.cpp
	CompileRootMacro MakeGenPlots.cpp Execute
