g++ source/BasicUtilities.cpp -I. -c -o library/BasicUtilities.o \
   -I$HOME/RootMacros/
g++ source/Messenger.cpp -I. -c -o library/Messenger.o `root-config --cflags` -std=c++11
g++ source/CATree.cpp -I. -c -o library/CATree.o -I/afs/cern.ch/user/c/chenyi/RootMacros/
g++ source/SDJetHelper.cpp -I. -c -o library/SDJetHelper.o -I/afs/cern.ch/user/c/chenyi/RootMacros/ \
   `root-config --cflags` -std=c++11
g++ source/EventMatching.cpp -I. -c -o library/EventMatching.o `root-config --cflags` -std=c++11

CompileRootMacro source/ScaleHistograms.cpp bin/ScaleHistograms
# CompileRootMacro source/AttachTags.cpp bin/AttachTags

