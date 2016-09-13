export FASTJET=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
CompileRootMacro JetMassPlots.cpp a.out \
   -I../../CommonCode/include ../../CommonCode/library/* \
   ~/RootMacros/Code/library/DrawRandom.o \
   ~/RootMacros/Code/library/TauHelperFunctions2.o \
   `$FASTJET/fastjet-config --cxxflags` `$FASTJET/fastjet-config --libs`
