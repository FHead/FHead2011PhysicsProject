g++ LeptonResponse.cc -c -o LeptonResponse.o -I ~/RootMacros/
CompileRootMacro PlotLeptonResponse.cpp a.out LeptonResponse.o 
CompileRootMacro CheckIntegration.cpp b.out LeptonResponse.o 

