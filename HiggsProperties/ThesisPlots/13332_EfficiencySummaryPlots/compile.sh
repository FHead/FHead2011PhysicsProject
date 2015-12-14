g++ LeptonResponse.cc -c -o LeptonResponse.o -I ~/RootMacros/ ~/RootMacros/Code/library/*o
g++ MakeEfficiencyPlot.cpp -o RunEfficiencyPlot -I ~/RootMacros/ ~/RootMacros/Code/library/*o LeptonResponse.o \
   `root-config --cflags` `root-config --glibs`
g++ MakeWidthPlot.cpp -o RunWidthPlot -I ~/RootMacros/ ~/RootMacros/Code/library/*o LeptonResponse.o \
   `root-config --cflags` `root-config --glibs`
g++ MakeWidthPlot2.cpp -o RunWidthPlot2 -I ~/RootMacros/ ~/RootMacros/Code/library/*o LeptonResponse.o \
   `root-config --cflags` `root-config --glibs`
g++ MakeTranserFunctionExamplePlot.cpp -o RunTransferFunctionPlot -I ~/RootMacros/ ~/RootMacros/Code/library/*o LeptonResponse.o \
   `root-config --cflags` `root-config --glibs`

