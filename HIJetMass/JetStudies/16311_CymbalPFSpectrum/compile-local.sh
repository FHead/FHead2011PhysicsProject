CompileRootMacro JetMassPlots.cpp RunSmear Class.o \
   -I../../CommonCode/include ../../CommonCode/library/* \
   `fastjet-config --cxxflags` `fastjet-config --libs` \
   /Users/yichen/Programs/fastjet/fastjet-3.2.1/../install321/lib/*.a
CompileRootMacro MakePlainTree.cpp RunPlain \
   -I../../CommonCode/include ../../CommonCode/library/*o \
   `fastjet-config --libs` `fastjet-config --cxxflags` \
   Class.o
