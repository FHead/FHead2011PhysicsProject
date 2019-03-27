default: TestRun

TestRun: Execute
	./Execute --Input RunSkimR03.root --OutputBase SkimR03
	cp SkimR03.pdf ~/public/html

Execute: Analyze.cpp
	CompileRootMacro Analyze.cpp Execute
