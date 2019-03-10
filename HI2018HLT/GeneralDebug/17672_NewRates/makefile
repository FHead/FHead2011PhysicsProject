default: TestRun

Execute: PrintRate.cpp
	CompileRootMacro PrintRate.cpp Execute

TestRun: Execute
	./Execute --Input TriggerList.txt --OpenHLT Output/openHLT_MinBias_V1V15_NewRaw.root | tee RateResult.txt

