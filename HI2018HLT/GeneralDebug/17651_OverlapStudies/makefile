default: TestRun

Execute: CalculateOverlap.cpp
	g++ CalculateOverlap.cpp `root-config --cflags --libs` -o Execute

TestRun: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros ./Execute \
		--L1 L1List.txt --HLT HLTList.txt --OpenHLT openHLT_MinBias.root --MBRate 50000
