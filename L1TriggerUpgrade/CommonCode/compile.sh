mkdir -p library

rootcint -f source/L1Classes.cpp -c include/L1Classes.h include/L1LinkDef.h
g++ `root-config --cflags` source/L1Classes.cpp -o library/L1Classes.o -I. -c -fpic
g++ `root-config --libs` library/L1Classes.o -shared -o library/L1Classes.so

CompileRootMacro source/Messenger.cpp library/Messenger.o -Iinclude -c | grep -v warning
