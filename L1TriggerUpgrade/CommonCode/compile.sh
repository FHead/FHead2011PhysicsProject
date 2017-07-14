mkdir -p library

rootcint -f source/L1Classes.cpp -c include/L1Classes.h include/L1LinkDef.h
CompileRootMacro source/L1Classes.cpp library/L1Classes.o -I. -c | grep -v warning

CompileRootMacro source/Messenger.cpp library/Messenger.o -Iinclude -c | grep -v warning
