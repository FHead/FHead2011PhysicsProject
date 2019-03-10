default: TestRun

Execute: RunToy.cpp
	CompileRootMacro RunToy.cpp Execute

TestRun: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros \
		./Execute \
		--tries 100000000 \
		--output ToyResult.pdf \
		--k 2.5 --min 10 --max 500 \
		--c0 0.00155 --c1 0.08802 --c2 13.41 \
		--binmin 50 --binmax 51 \
		--exclude 0.015

TestRun2: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros \
		./Execute \
		--tries 100000000 \
		--output ToyResult.pdf \
		--k 0.0 --min 10 --max 500 \
		--c0 0.0081 --c1 0.0 --c2 0.0 \
		--binmin 50 --binmax 51 \
		--exclude 0.015





