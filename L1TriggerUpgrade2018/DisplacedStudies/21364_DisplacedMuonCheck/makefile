default: TestRun

Execute: CheckDisplaced.cpp
	CompileRootMacro CheckDisplaced.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`fastjet-config --cxxflags --libs`

TestRun: Execute
	./Execute --input SamplesDarkPhoton/L1NtuplePhaseII_1.root \
		--output Test.root


