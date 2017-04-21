CompileRootMacro MakePlainTree.cpp Run \
   -I../../CommonCode/include ../../CommonCode/library/*o \
   `fastjet-config --libs` `fastjet-config --cxxflags`
