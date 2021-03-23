N = 100000

default:
	echo Hello world

RunPythia: Execute
	time ./Execute --Output PurePythia.root --N $(N)

Execute: GeneratePythia.cpp
	CompileRootMacro GeneratePythia.cpp Execute
