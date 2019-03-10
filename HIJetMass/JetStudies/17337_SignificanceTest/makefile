default: ExecuteSignificance ExecuteDiscriminantPlot

ExecuteSignificance: RunSignificance 
	./RunSignificance > Log
	grep "^TEST " Log | awk '{print $$2,$$3}' | TextToTree Result.root 2 "D:S"

ExecuteDiscriminantPlot: RunDiscriminantPlot
	./RunDiscriminantPlot `grep Observed Log | awk '{print $$2}'`
	cp KSTest.pdf ~/public/html/

RunSignificance: CalculateSignificance.cpp
	CompileRootMacro CalculateSignificance.cpp RunSignificance

RunDiscriminantPlot: DrawDiscriminantPlot.cpp
	CompileRootMacro DrawDiscriminantPlot.cpp RunDiscriminantPlot
