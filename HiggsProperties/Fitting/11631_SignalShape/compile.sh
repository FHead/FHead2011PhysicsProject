g++ FitSignalShapes.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   /home/yichen/RootMacros/Code/library/DrawRandom.o \
   /home/yichen/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/CalculateME.o \
   ../../CommonCode/library/RooDoubleSidedCBShape.o \
   ../../CommonCode/library/RooModifiedBreitWigner.o \
   `root-config --glibs` `root-config --cflags` \
   -I/cms/sw/slc5_amd64_gcc462/lcg/roofit/5.32.00-cms5/include \
   -L/cms/sw/slc5_amd64_gcc462/lcg/roofit/5.32.00-cms5/lib \
   -lRooFitCore -lRooFit -lMinuit -lFoam \
   -O2 \
   -o Run
g++ CalculateIntegral.cpp -I$HOME/RootMacros -I../../CommonCode/include \
   /home/yichen/RootMacros/Code/library/DrawRandom.o \
   /home/yichen/RootMacros/Code/library/TauHelperFunctions2.o \
   ../../CommonCode/library/AngleConversion.o \
   ../../CommonCode/library/CalculateME.o \
   ../../CommonCode/library/RooDoubleSidedCBShape.o \
   ../../CommonCode/library/RooModifiedBreitWigner.o \
   `root-config --glibs` `root-config --cflags` \
   -I/cms/sw/slc5_amd64_gcc462/lcg/roofit/5.32.00-cms5/include \
   -L/cms/sw/slc5_amd64_gcc462/lcg/roofit/5.32.00-cms5/lib \
   -lRooFitCore -lRooFit -lMinuit -lFoam \
   -O2 \
   -o DoIntegral
