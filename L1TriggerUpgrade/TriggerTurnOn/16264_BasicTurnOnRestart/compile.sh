CompileRootMacro Histograms.cpp Histograms.o -c -I../../CommonCode/include | grep -v warning
CompileRootMacro PlotTurnOn.cpp RunTurnOn \
   -I../../CommonCode/include ../../CommonCode/library/*.o \
   Histograms.o
