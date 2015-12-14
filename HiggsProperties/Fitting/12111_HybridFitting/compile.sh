CompileRootMacro ProjectionHelper.cpp ProjectionHelper.o -c -I ../../CommonCode/include
CompileRootMacro PTYFunctions.cpp PTYFunctions.o -c 
CompileRootMacro DoFit.cpp PerformFit -I ../../CommonCode/include ../../CommonCode/library/* ProjectionHelper.o PTYFunctions.o
