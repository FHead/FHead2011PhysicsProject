
default: TestRun

TestRun: Execute
	./Execute --input 20210218_CMSOpenData_HighPT_Part3.root --output 20210218_CMSOpenData_HighPT_Part3.txt \
		--fraction 1
	bzip2 20210218_CMSOpenData_HighPT_Part3.txt

Execute: Convert.cpp
	CompileRootMacro Convert.cpp Execute
