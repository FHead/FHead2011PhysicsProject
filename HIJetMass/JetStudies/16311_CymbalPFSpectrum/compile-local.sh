# FJ=/Users/yichen/Programs/fastjet/install321/
# FJ=/Users/yichen/Programs/fastjet/install321-1026/
FJ=/Users/yichen/Programs/fastjet/install321-1019/
# FJ=/Users/yichen/Programs/fastjet/install321-1014/

CompileRootMacro JetMassPlots.cpp RunSmear Class.o \
   -I../../CommonCode/include ../../CommonCode/library/* \
   `$FJ/bin/fastjet-config --cxxflags` `$FJ/bin/fastjet-config --libs` \
   $FJ/lib/*.a
CompileRootMacro MakePlainTree.cpp RunPlain \
   -I../../CommonCode/include ../../CommonCode/library/*o \
   `$FJ/bin/fastjet-config --libs` `$FJ/bin/fastjet-config --cxxflags` \
   Class.o
