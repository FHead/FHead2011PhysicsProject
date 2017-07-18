# FASTJET=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
# FASTCONTRIB=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet-contrib/1.014/
# FASTCONTRIB=/afs/cern.ch/user/c/chenyi/Programs/fastjet/install
# FASTJET=/afs/cern.ch/user/c/chenyi/work/Programs/fastjet/install/bin
# FASTCONTRIB=/afs/cern.ch/user/c/chenyi/work/Programs/fastjet/install

FJ=/Users/yichen/Programs/fastjet/install321-1026/

echo Compiling RunSmear
CompileRootMacro JetMassPlots.cpp RunSmear Class.o \
   -I../../CommonCode/include ../../CommonCode/library/* \
   `$FJ/bin/fastjet-config --cxxflags` `$FJ/bin/fastjet-config --libs` \
   $FJ/lib/*.a

