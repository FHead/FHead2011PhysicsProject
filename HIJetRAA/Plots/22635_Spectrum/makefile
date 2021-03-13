default: TestRun

TestRun: Execute
	./Execute

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
	cp Spectra.pdf ~/public/html/
