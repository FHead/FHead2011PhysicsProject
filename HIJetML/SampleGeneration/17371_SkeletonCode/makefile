default: TestRun

Execute: AccessJetImage.cpp
	g++ `root-config --libs --cflags` AccessJetImage.cpp -o Execute

TestRun: Execute
	./Execute --input Example.root --output TestRun.pdf --minjetpt 270
