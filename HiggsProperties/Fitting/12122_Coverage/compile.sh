CompileRootMacro ProjectionHelper.cpp ProjectionHelper.o -c -I ../../CommonCode/include
CompileRootMacro DoFit.cpp PerformFit -I ../../CommonCode/include ../../CommonCode/library/* ProjectionHelper.o
