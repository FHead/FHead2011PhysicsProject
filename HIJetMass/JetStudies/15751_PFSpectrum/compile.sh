export FASTJET=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
export FASTCONTRIB=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet-contrib/1.014/

echo Compiling RunSmear
CompileRootMacro JetMassPlots.cpp RunSmear \
   -I../../CommonCode/include ../../CommonCode/library/* \
   `$FASTJET/fastjet-config --cxxflags` `$FASTJET/fastjet-config --libs` \
   -I$FASTCONTRIB/include $FASTCONTRIB/lib/*.a

echo Compiling Run
CompileRootMacro MakePlainTree.cpp Run \
   -I../../CommonCode/include ../../CommonCode/library/*o \
   `$FASTJET/fastjet-config --cxxflags` `$FASTJET/fastjet-config --libs` \
   -I$FASTCONTRIB/include $FASTCONTRIB/lib/*.a
