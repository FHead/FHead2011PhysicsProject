

default: TestRun

TestRun: Execute
	./Execute --range 0,2,0,20,0,2,0,20 --tries 1000000 > Matter.txt
	./Execute --range 0,2,0,20,0,2,0,20 --tries 1000000 > LBT.txt
	./Execute --range 0,1.5,0,1,0,20,0,20,1,4 --tries 1000000 > MatterLBT1.txt
	./Execute --range 0,2,0,1,0,20,1,4 --tries 1000000 > MatterLBT2.txt

Execute: GenerateBlock.cpp
	CompileRootMacro GenerateBlock.cpp Execute
