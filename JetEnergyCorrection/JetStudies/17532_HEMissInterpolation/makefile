export LD_LIBRARY_PATH = /Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros

default: TestRunFinal

Execute: DeriveResponse.cpp
	CompileRootMacro DeriveResponse.cpp Execute

ExecuteFinal: InterpolateFunction.cpp
	CompileRootMacro InterpolateFunction.cpp ExecuteFinal

TestRun: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros \
		./Execute --input Sample1.root --output Good.pdf --algorithm ak4pf \
		   --phimin 0 --phimax 3.14
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros \
		./Execute --input Sample1.root --output Bad.pdf --algorithm ak4pf \
		   --phimin -1.6 --phimax -0.9

TestRunFinal: ExecuteFinal
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros \
		./ExecuteFinal --input Sample1.root --output Plots.pdf --algorithm ak4pf



