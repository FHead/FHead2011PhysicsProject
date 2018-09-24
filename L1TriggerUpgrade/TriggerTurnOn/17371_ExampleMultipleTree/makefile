default: ExecuteExample

L1Classes.so: L1*.h L1Classes.cpp
	rootcint -f L1Classes.cpp -c L1Classes.h L1LinkDef.h
	g++ `root-config --cflags` L1Classes.cpp -o L1Classes.o -I. -c -fpic
	# g++ -shared -o L1Classes.so L1Classes.o

RunExample: Example.cpp L1Classes.o
	g++ `root-config --cflags --libs` Example.cpp -o RunExample L1Classes.o

ExecuteExample: RunExample
	./RunExample --input Hgaga_E2023TTI_PU200_25.root --output Example.pdf
