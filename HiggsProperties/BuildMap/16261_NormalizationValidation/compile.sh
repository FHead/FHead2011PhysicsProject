CompileRootMacro CheckNormalization.cpp Run -std=c++11 \
   -I ../../CommonCode/include \
   ../../CommonCode/library/Cuts.o \
   ../../CommonCode/library/AngleConversion.o
CompileRootMacro CheckSomeAs.cpp RunAs -std=c++11 \
   -I ../../CommonCode/include \
   ../../CommonCode/library/Cuts.o \
   ../../CommonCode/library/AngleConversion.o
