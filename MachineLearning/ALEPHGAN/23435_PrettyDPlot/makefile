

default: TestRun

TestRun: Execute
	./Execute

Execute: MakePlot.cpp
	g++ MakePlot.cpp -o Execute `root-config --cflags --glibs`
