default: TestRun

TestRun: Execute
	./Execute --PythiaAbove false
	./Execute --PythiaAbove true
	./Execute --R1 3 --R2 4 --PythiaAbove false
	./Execute --R1 3 --R2 4 --PythiaAbove true
	./Execute --R1 6 --R2 8 --PythiaAbove false
	./Execute --R1 6 --R2 8 --PythiaAbove true
	cp *pdf ~/public/html/

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute
