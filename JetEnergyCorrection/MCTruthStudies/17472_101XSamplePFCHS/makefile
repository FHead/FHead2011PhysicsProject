default: TestRun

Execute: CheckCHS.cpp
	CompileRootMacro CheckCHS.cpp Execute

TestRun: Execute
	time ./Execute --input JRA.root --output CHSCheck.pdf
	time ./Execute --input JRA2017.root --output CHSCheck2017.pdf
	time ./Execute --input JRA2.root --output CHSCheck2018DefaultCHS.pdf --pf ak4pf --pfchs ak4pfchsAOD
	time ./Execute --input JRA2.root --output CHSSanity.pdf --pf ak4pfchs --pfchs ak4pfchsAOD



