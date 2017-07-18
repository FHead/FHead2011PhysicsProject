CompileRootMacro ReadTree.cpp ReadTree.o -c | grep -v warning
CompileRootMacro MBReadTree.cpp MBReadTree.o -c | grep -v warning
CompileRootMacro SmearTreeUnitTest.cpp RunTest MBReadTree.o

