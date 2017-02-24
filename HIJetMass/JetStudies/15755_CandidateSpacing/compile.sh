CompileRootMacro CandidateSpacing.cpp a.out -I ../../CommonCode/include/ ../../CommonCode/library/*
CompileRootMacro CandidateSpacingInJet.cpp b.out -I ../../CommonCode/include/ ../../CommonCode/library/*
CompileRootMacro CandidateSpacingRandom.cpp c.out -I ../../CommonCode/include/ ../../CommonCode/library/* \
   `fastjet-config --cxxflags` `fastjet-config --libs` \
   /Users/yichen/Programs/fastjet/fastjet-3.2.1/../install321/lib/*.a \
   Class.o
