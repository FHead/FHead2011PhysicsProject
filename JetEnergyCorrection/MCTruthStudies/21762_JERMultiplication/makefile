default: TestRun

TestRun: Execute
	./Execute --JERFileName Autumn18_V7_MC_PtResolution_AK4PFchs.txt --JERSFFileName Autumn18_V7_MC_SF_AK4PFchs.txt --Output Autumn18_V7_Data_PtResolution_AK4PFchs.txt

DebugRun: Execute
	./Execute --JERFileName TestJER.txt --JERSFFileName TestJERSF.txt --Output Test.txt

Execute: MultiplyTextFiles.cpp
	CompileRootMacro MultiplyTextFiles.cpp Execute -g
