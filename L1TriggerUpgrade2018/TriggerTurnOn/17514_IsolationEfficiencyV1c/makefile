default: TestRun

Execute: MakeEfficiencyPlots.cpp
	CompileRootMacro MakeEfficiencyPlots.cpp Execute

TestRun: Execute
	./Execute --input TTbar.root --output Meow.pdf
	cp Meow.pdf ~/public/html/
