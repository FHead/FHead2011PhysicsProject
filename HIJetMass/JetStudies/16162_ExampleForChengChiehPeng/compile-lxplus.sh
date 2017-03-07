FastJet=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.1.0/
FastJetContrib=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet-contrib/1.014/

g++ source/Messenger.cpp -c -o Messenger.o -I. `root-config --cflags`
g++ ExampleFastJetSoftDrop.cpp -o RunExample -Iinclude \
   `root-config --libs` `root-config --cflags` \
   Messenger.o \
   `$FastJet/bin/fastjet-config --libs` `$FastJet/bin/fastjet-config --cxxflags` \
   -I$FastJetContrib/include $FastJetContrib/lib/*
