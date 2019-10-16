default: TestRun

TestRun: Execute
	./Execute --PythiaAbove false
	./Execute --PythiaAbove true

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
