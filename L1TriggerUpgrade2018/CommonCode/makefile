default: library/L1Classes.so library/Messenger.o

library/L1Classes.so: include/L1Classes.h include/L1LinkDef.h
	mkdir -p library
	rootcint -f source/L1Classes.cpp -c include/L1Classes.h include/L1LinkDef.h
	g++ `root-config --cflags` source/L1Classes.cpp -o library/L1Classes.o -I. -c -fpic
	g++ -shared -o library/L1Classes.so library/L1Classes.o

library/Messenger.o: source/Messenger.cpp
	CompileRootMacro source/Messenger.cpp library/Messenger.o -Iinclude -c | grep -v warning

