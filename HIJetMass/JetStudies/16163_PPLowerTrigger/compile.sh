export FASTJET=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
export FASTCONTRIB=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet-contrib/1.014/
CompileRootMacro JetMassPlots.cpp a.out \
   -I../../CommonCode/include ../../CommonCode/library/* \
   `$FASTJET/fastjet-config --cxxflags` `$FASTJET/fastjet-config --libs` \
   -I$FASTCONTRIB/include $FASTCONTRIB/lib/*.a
# CompileRootMacro JetMassPlots.cpp b.out \
#    -I../../CommonCode/include ../../CommonCode/library/* \
#    `$FASTJET/fastjet-config --cxxflags` `$FASTJET/fastjet-config --libs` \
#    -I$FASTCONTRIB/include $FASTCONTRIB/lib/*.a
# echo
# echo Compiled into b.out for debugging purposes
# echo
