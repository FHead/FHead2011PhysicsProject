# export FASTJET=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.0.3-cms2/bin/
# export FASTCONTRIB=/afs/cern.ch/user/c/chenyi/Programs/fastjet/install
FJ=/Users/yichen/Programs/fastjet/install321-1026/

CompileRootMacro GenStudy.cpp Run \
   -I../../CommonCode/include ../../CommonCode/library/*o \
   `$FJ/bin/fastjet-config --cxxflags` `$FJ/bin/fastjet-config --libs` \
   $FJ/lib/*.a
