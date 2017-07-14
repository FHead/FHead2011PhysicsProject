export FASTJET=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
export FASTCONTRIB=/afs/cern.ch/user/c/chenyi/Programs/fastjet/install

g++ GenLevelCheck.cpp -o RunCheck \
   `root-config --libs` `root-config --cflags` \
   -I$RootMacrosBase $RootMacrosBase/Code/library/* \
   -I../../CommonCode/include ../../CommonCode/library/* \
   `$FASTJET/fastjet-config --cxxflags` `$FASTJET/fastjet-config --libs` \
   -I$FASTCONTRIB/include $FASTCONTRIB/lib/*.a
