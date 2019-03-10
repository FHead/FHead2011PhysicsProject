default: TestRun

Execute: EfficiencyPlots.cpp
	CompileRootMacro EfficiencyPlots.cpp Execute

TestRun: Execute
	./Execute --input TTbar.root --output Meow.pdf --outputfull MeowFull.pdf
	cp Meow.pdf MeowFull.pdf ~/public/html/




