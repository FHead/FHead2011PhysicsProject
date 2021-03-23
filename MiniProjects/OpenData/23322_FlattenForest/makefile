
default: TestRun

TestRun: Execute
	./Execute --input 20210203_CMSOpenData10k.root --output 20210203_CMSOpenData10k.txt

Execute: Convert.cpp
	CompileRootMacro Convert.cpp Execute
