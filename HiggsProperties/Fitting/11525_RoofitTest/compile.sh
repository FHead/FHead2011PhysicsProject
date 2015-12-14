g++ Fitting.cpp -I$HOME/RootMacros -I../../CommonCode/include $HOME/RootMacros/Code/library/DrawRandom.o $HOME/RootMacros/Code/library/TauHelperFunctions2.o ../../CommonCode/library/AngleConversion.o ../../CommonCode/library/CalculateME.o ../../CommonCode/library/RooMeow.o `root-config --glibs` `root-config --cflags` -lRooFitCore -lRooFit -lMinuit -lFoam -lMathMore -lHistPainter -O2 -o Run

