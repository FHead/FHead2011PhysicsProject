export FASTJET=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
export FASTCONTRIB=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet-contrib/1.014/
CompileRootMacro CSCheck.cpp RunCheck -I ../../CommonCode/include ../../CommonCode/library/* \
   `$FASTJET/fastjet-config --libs` `$FASTJET/fastjet-config --cxxflags` \
   -I$FASTCONTRIB/include $FASTCONTRIB/lib/libConstituentSubtractor.a
CompileRootMacro CSCheckPartII.cpp RunCheckPartII -I ../../CommonCode/include ../../CommonCode/library/* \
   `$FASTJET/fastjet-config --libs` `$FASTJET/fastjet-config --cxxflags` \
   -I$FASTCONTRIB/include $FASTCONTRIB/lib/*.a
CompileRootMacro CSCheckPartIII.cpp RunCheckPartIII -I ../../CommonCode/include ../../CommonCode/library/* \
   `$FASTJET/fastjet-config --libs` `$FASTJET/fastjet-config --cxxflags` \
   -I$FASTCONTRIB/include $FASTCONTRIB/lib/*.a
