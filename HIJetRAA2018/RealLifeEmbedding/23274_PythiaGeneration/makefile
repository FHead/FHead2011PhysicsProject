N = 100000

default:
	echo Hello world

RunPythia: Execute
	time ./Execute --Output PurePythia.root --N $(N)

RunPythia250: Execute
	time ./Execute --Output PurePythia250.root --N $(N) --PTHat 250

Execute: GeneratePythia.cpp
	CompileRootMacro GeneratePythia.cpp Execute
