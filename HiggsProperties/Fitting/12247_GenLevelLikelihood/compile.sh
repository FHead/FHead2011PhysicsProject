CompileRootMacro ProjectionHelper.cpp ProjectionHelper.o -c -I ../../CommonCode/include
CompileRootMacro PTYFunctions.cpp PTYFunctions.o -c 
CompileRootMacro FitClass.cpp FitClass.o -c -I ../../CommonCode/include
CompileRootMacro DoFit.cpp LikelihoodPlotsMeow -I ../../CommonCode/include ../../CommonCode/library/* ProjectionHelper.o PTYFunctions.o FitClass.o
