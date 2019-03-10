default: TestRunFHeadMac

Execute: CalculateOverlap.cpp
	g++ CalculateOverlap.cpp `root-config --cflags --libs` -o Execute

TestRunFHeadMac: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros ./Execute \
		--L1 L1List.txt --HLT HLTList.txt --OpenHLT openHLT_MinBias.root --MBRate 50000

TestRun: Execute
	./Execute --L1 L1List.txt --HLT HLTList.txt --OpenHLT openHLT_MinBias.root --MBRate 50000
