CompileRootMacro ProjectionHelper.cpp ProjectionHelper.o -c -I ../../CommonCode/include
CompileRootMacro DoFit.cpp a.out -I ../../CommonCode/include ../../CommonCode/library/* ProjectionHelper.o
