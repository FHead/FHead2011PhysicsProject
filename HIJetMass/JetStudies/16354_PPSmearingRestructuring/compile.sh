export FASTJET=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
# export FASTCONTRIB=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet-contrib/1.014/
# export FASTCONTRIB=/afs/cern.ch/user/c/chenyi/Programs/fastjet/install
# export FASTJET=/afs/cern.ch/user/c/chenyi/work/Programs/fastjet/install/bin
export FASTCONTRIB=/afs/cern.ch/user/c/chenyi/work/Programs/fastjet/install

# echo Compiling RunSmear - into a RunSmearMeow for debugging purposes
CompileRootMacro JetMassPlots.cpp RunSmear \
   -I../../CommonCode/include ../../CommonCode/library/* \
   `$FASTJET/fastjet-config --cxxflags` `$FASTJET/fastjet-config --libs` \
   -I$FASTCONTRIB/include $FASTCONTRIB/lib/*.a
# echo RunSmearMEOW compiled
