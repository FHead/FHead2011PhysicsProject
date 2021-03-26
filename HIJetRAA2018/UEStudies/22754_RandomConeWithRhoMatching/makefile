

default: TestRun

TestRun: Execute
	./Execute --data CurvesData.root --mc CurvesMC.root
	cp *pdf ~/public/html/

Execute: UEMatching.cpp
	CompileRootMacro UEMatching.cpp Execute

