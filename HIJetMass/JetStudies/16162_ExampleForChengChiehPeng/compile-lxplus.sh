echo This setup assumes you have setup a CMSSW version with SCRAM_ARCH = slc6_amd64_gcc491...for example CMSSW_7_5_8_patch3.  If you use others, make sure to change the directories of fastjet and fastjet-contrib - should be easy to find in cvmfs

FastJet=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet/3.1.0/
FastJetContrib=/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/fastjet-contrib/1.014/

echo Current fastjet and fastjet-contrib set to...
echo fastjet: $FastJet
echo fastjet-contrib: $FastJetContrib

g++ source/Messenger.cpp -c -o Messenger.o -I. `root-config --cflags`
g++ ExampleFastJetSoftDrop.cpp -o RunExample -Iinclude \
   `root-config --libs` `root-config --cflags` \
   Messenger.o \
   `$FastJet/bin/fastjet-config --libs` `$FastJet/bin/fastjet-config --cxxflags` \
   -I$FastJetContrib/include $FastJetContrib/lib/*
